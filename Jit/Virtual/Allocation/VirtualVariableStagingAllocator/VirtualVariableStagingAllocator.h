//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "OsxSystemRegisterPriorityQueue.h"
#include "VirtualVariableStackPersistenceStage.h"
#include "ProcessorOpCodeSet.h"
#import "ArgumentStagingRegisterAssignmentFactory.h"

#ifndef __VirtualVariableStagingAllocator_H_
#define __VirtualVariableStagingAllocator_H_

namespace jit {
  class VirtualVariableStagingAllocator {
    op::ProcessorOpCodeSet& jit_opcodes_;
    VirtualVariableStackPersistenceStage stack_persistence_stage_;
    OsxSystemRegisterPriorityQueue register_queue_;
    ArgumentStagingRegisterAssignmentFactory argument_staging_factory_;

    // Variables that are neither on the stack nor register bound.
    std::vector<VirtualVariable> unstaged_variables_;


  public:
    VirtualVariableStagingAllocator(op::ProcessorOpCodeSet& jit_opcodes, size_t size)
      : stack_persistence_stage_(size),
        jit_opcodes_(jit_opcodes) {
      unstaged_variables_.resize(size);
    }

    // Debug
    void show() {
      /*for (int index)
          if (item.contains_variable()) {
              std::cout << item.variable_number() << ": " << item.sys_register() << std::endl;
          }
      }*/
    }

    bool contains_variable(int variable_number) {
      return (is_variable_unstaged(variable_number)
        || is_stack_persisted(variable_number)
        || is_bound_to_register(variable_number));
    }

    VirtualVariable& operator[](int variable_number) {
      if (is_variable_unstaged(variable_number)) {
        return unstaged_variables_[variable_number];

      } else if (is_stack_persisted(variable_number)) {
        return stack_persistence_stage_[variable_number];

      } else if (is_bound_to_register(variable_number)) {
        return register_queue_.borrow_variable(variable_number);
      }

      throw std::logic_error("variable at index is not in use");
    }

    // Create a new local
    void new_local(VirtualVariable&& variable) {
      validate_variable(variable);
      unstaged_variables_[variable.variable_number()] = std::move(variable);
    }

    void new_local(int variable_number, const types::SystemType& type,
      int priority, bool is_member, bool is_class_pointer) {

      new_local(std::move(VirtualVariable(variable_number, type, priority, is_member, is_class_pointer)));
    }

    void persist_variables() {
      argument_staging_factory_.reset();

      for (int binding_index = 0; binding_index != register_queue_.size(); ++binding_index) {
        register_queue_.with_binding_by_bindnum(binding_index,
          [&](VirtualVariableSystemRegisterBinding& binding) {

            // If the binding is locked, it's because it's being used
            // as a parameter. No need to store parameters.
            if (binding.contains_variable()) {
              binding.unlock();
              stack_persist(binding);
            }
          });
      }
    }


    // Bind a variable to a specific register.
    void stage_argument(int variable_index) {
      auto cpu_register = argument_staging_factory_.determine_register();

      lock_variable_to_register(cpu_register, variable_index);
    }

    // Callback for performing tasks with a single register.
    void with_register(int variable_number, std::function<void(VirtualVariableCheckout&)> callback) {
      bind_to_system_register(variable_number);

      register_queue_.with_binding_by_varnum(variable_number,
        [&](VirtualVariableSystemRegisterBinding& binding) {
          VirtualVariableCheckout checkout(jit_opcodes_, binding.sys_register(), binding.variable());
          callback(checkout);
        });
    }

    // Callback for performing tasks with two registers.
    /*void with_register(int lhs_register_number, int rhs_register_number,
        std::function<void(VirtualVariableCheckout&, VirtualVariableCheckout&)> callback) {

        //register_queue_.with_register(lhs_register_number, rhs_register_number, callback);
    }*/

  private:
    void empty_registers_for_locking(const arch::CpuRegister& sys_register, int variable_number) {
      // First make sure the register is empty. Or if we're already bound to it.
      if (does_register_hold_data(sys_register)) {

        register_queue_.with_binding_by_register(sys_register,
          [&](VirtualVariableSystemRegisterBinding& binding) {

            // If this variable is already bound. Then go ahead and lock it, then return.
            if (binding.variable_number() == variable_number) {
              binding.lock();
              register_queue_.update_binding(std::move(binding));
              return;
            }

            // Otherwise, persist this variable to memory.
            stack_persist(binding);

          });

      }


      // If the variable is already bound to another register,
      // Emit an opcode that moves the value between registers.
      if (is_bound_to_register(variable_number)) {

        // THIS SHOULDN'T BE TRUE FOR 3.
        register_queue_.with_binding_by_varnum(variable_number,
          [&](VirtualVariableSystemRegisterBinding& binding) {

            // If we're already correctly bound. Return.
            if (binding.sys_register() == sys_register) {
              register_queue_.update_binding(std::move(binding));
              binding.lock();
              return;
            }

            // Move the binding to the unstaged area.
            VirtualVariable&& variable = std::move(binding.release_variable());
            unstaged_variables_[variable.variable_number()] = std::move(variable);

            // Emit the opcode saying that the register has moved.
            jit_opcodes_.mov(sys_register, binding.sys_register());

          });
      }
    }


    void perform_register_lock(const arch::CpuRegister& sys_register, int variable_index) {
      // Now that the variable has been freed (and is now unstaged)
      // Rebind it to the corect destination register.
      if (is_stack_persisted(variable_index)) {
        register_queue_.with_binding_by_register(sys_register,
          [&](VirtualVariableSystemRegisterBinding& binding) {
            VirtualVariable&& variable = std::move(stack_persistence_stage_.release(variable_index));
            const static auto& rbp = arch::Intelx64Registers::rbp;
            jit_opcodes_.mov(binding.sys_register(), rbp[(int) calculate_persistence_offset(variable)]);

            binding.bind_variable(std::move(variable));
          });

      }
      else if (is_variable_unstaged(variable_index)) {
        // Finally check out the register we want, and bind.
        // Assuming for the moment the variable is unstaged.
        VirtualVariable&& variable = std::move(unstaged_variables_[variable_index]);
        register_queue_.with_binding_by_register(sys_register,
          [&](VirtualVariableSystemRegisterBinding& binding) {
            binding.bind_variable(std::move(variable));
          });

      }
    }

    // Bind a variable to a specific register.
    void lock_variable_to_register(const arch::CpuRegister& sys_register, int variable_index) {
      empty_registers_for_locking(sys_register, variable_index);
      perform_register_lock(sys_register, variable_index);
    }


    // Not sure if this is neccesary.
    void bind_to_system_register(int variable_number) {
      if (!is_bound_to_register(variable_number)) {

        if (is_variable_unstaged(variable_number)) {
          register_queue_.with_binding_by_availability([&](VirtualVariableSystemRegisterBinding& binding) {
            VirtualVariable&& variable = std::move(unstaged_variables_[variable_number]);
            validate_variable(variable);

            // If something is already there, then persist it first.
            persist_if_contains_variable(binding);
            binding.bind_variable(std::move(variable));
          });
        }

        if (is_stack_persisted(variable_number)) {
          // Grab the variable from the stack, and then capture a register to bind to.
          register_queue_.with_binding_by_availability([&](VirtualVariableSystemRegisterBinding& binding) {
            VirtualVariable&& variable = std::move(stack_persistence_stage_.release(variable_number));

            // If there is already something in the biding, persist it.
            persist_if_contains_variable(binding);

            // Since we're moving from memory, we need to emit an opcode that represents that move.
            const static auto& rbp = arch::Intelx64Registers::rbp;
            jit_opcodes_.mov(binding.sys_register(), rbp[(int) calculate_persistence_offset(variable)]);

            binding.bind_variable(std::move(variable));
          });

        }
      }
    }

    void persist_if_contains_variable(VirtualVariableSystemRegisterBinding& binding) {
      if (binding.contains_variable()) {
        stack_persist(binding);
      }
    }

    bool is_variable_unstaged(int variable_number) {
      return !unstaged_variables_[variable_number].is_empty();
    }

    bool is_stack_persisted(int variable_number) {
      return stack_persistence_stage_.contains_variable(variable_number);
    }

    bool is_bound_to_register(int variable_number) {
      return register_queue_.is_bound(variable_number);
    }

    bool does_register_hold_data(const arch::CpuRegister& reg) {
      return register_queue_.is_bound(reg);
    }

    void stack_persist(VirtualVariableSystemRegisterBinding& binding) {
      const static auto& rbp = arch::Intelx64Registers::rbp;

      // Release the variable from the binding.
      VirtualVariable variable = std::move(binding.release_variable());

      // Emit an opcode stating the movement from system register (binding) to the stack.
      jit_opcodes_.mov(rbp[(int) calculate_persistence_offset(variable)], binding.sys_register());

      // Release the variable and bind it to the stack
      stack_persistence_stage_.persist_variable(binding.sys_register(), std::move(variable));
    }

    void validate_variable(const VirtualVariable& variable) {
      if (variable.is_empty()) {
        throw std::logic_error("variable is invalid");
      }

      if (variable.variable_number() > stack_persistence_stage_.size()) {
        throw std::logic_error("variable number is larger than allocated stack space");
      }
    }

    off_t calculate_persistence_offset(const VirtualVariable& variable) {
      const static off_t stack_variable_size = sizeof(uint64_t);

      // Negative because the stack grows downward.
      // variable_number * variable_size + 8
      // +8 because the first address is reserved for the base pointer (rbp).
      // The rpb holds a pointer to the previous stack frame base.
      return -(stack_variable_size * variable.variable_number() + 8);
    }
  };
}


#endif //__VirtualVariableStagingAllocator_H_
