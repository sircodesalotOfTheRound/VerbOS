//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VirtualVariableSystemRegisterStage.h"
#include "VirtualVariableStackPersistenceStage.h"
#include "ProcessorOpCodeSet.h"

#ifndef __VirtualVariableStagingAllocator_H_
#define __VirtualVariableStagingAllocator_H_

namespace jit {
    class VirtualVariableStagingAllocator {
        op::ProcessorOpCodeSet& jit_opcodes_;
        VirtualVariableStackPersistenceStage stack_persistence_stage_;
        VirtualVariableSystemRegisterStage sys_register_stage_;

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
            sys_register_stage_.show();
        }

        // Create a new local
        void new_local(VirtualVariable&& variable) {
            validate_variable(variable);

            unstaged_variables_[variable.variable_number()] = std::move(variable);
        }

        void unlock_register_bindings() {
            sys_register_stage_.unlock_bindings();
        }

        // Bind a variable to a specific register.
        void lock_to_system_register(const arch::CpuRegister& sys_register, int variable_index) {
            VirtualVariable&& variable = release_variable(variable_index);
            VirtualVariableSystemRegisterBinding&& binding
                = std::move(sys_register_stage_.dequeue_binding(sys_register));

            binding.lock();

            apply_binding(std::move(variable), std::move(binding));
        }

        // Callback for performing tasks with a single register.
        void with_register(int variable_number, std::function<void(VirtualVariableCheckout&)> callback) {
            bind_to_system_register(variable_number);
            sys_register_stage_.with_register(variable_number, callback);
        }

        // Callback for performing tasks with two registers.
        void with_register(int lhs_register_number, int rhs_register_number,
            std::function<void(VirtualVariableCheckout&, VirtualVariableCheckout&)> callback) {

            sys_register_stage_.with_register(lhs_register_number, rhs_register_number, callback);
        }

    private:

        // Not sure if this is neccesary.
        void bind_to_system_register(int variable_number) {
            if (!is_register_staged(variable_number)) {
                VirtualVariable&& variable = release_variable(variable_number);
                VirtualVariableSystemRegisterBinding&& binding = std::move(sys_register_stage_.dequeue_binding());

                apply_binding(std::move(variable), std::move(binding));
            }
        }

        bool is_unstaged(int variable_number) {
            return !unstaged_variables_[variable_number].is_empty();
        }

        bool is_stack_persisted(int variable_number) {
            return stack_persistence_stage_.contains_variable(variable_number);
        }

        bool is_register_staged(int variable_number) {
            return sys_register_stage_.is_staged(variable_number);
        }

        VirtualVariable&& release_from_unstaged(int variable_number) {
            return std::move(unstaged_variables_[variable_number]);
        }

        VirtualVariable&& release_from_stack(int variable_number) {
            return std::move(stack_persistence_stage_.release(variable_number));
        }

        VirtualVariable&& release_from_register_binding(int variable_number) {
            return std::move(sys_register_stage_.release(variable_number));
        }

        VirtualVariable&& release_variable(int variable_number) {
            if (is_stack_persisted(variable_number)) {
                return release_from_stack(variable_number);

            }
            else if (is_register_staged(variable_number)) {
                return release_from_register_binding(variable_number);

            } else if (is_unstaged(variable_number)) {
                return release_from_unstaged(variable_number);

            }

            throw std::logic_error("variable was not staged");
        }


        void stack_persist(VirtualVariableSystemRegisterBinding& binding) {
            const static auto& rbp = arch::OsxRegisters::rbp;

            VirtualVariable& variable = binding.variable();
            validate_variable(variable);

            // Emit an opcode stating the movement from system register (binding) to the stack.
            jit_opcodes_.mov(rbp[calculate_persistence_offset(variable)], binding.sys_register());

            // Release the variable and bind it to the stack
            stack_persistence_stage_.persist_variable(binding.sys_register(), std::move(binding.release_variable()));
        }

        void apply_binding(VirtualVariable&& variable, VirtualVariableSystemRegisterBinding&& binding) {
            validate_variable(variable);

            // If something is already there, then persist it first.
            if (binding.contains_variable()) {
                stack_persist(binding);
            }

            binding.bind_variable(std::move(variable));
            sys_register_stage_.bind(std::move(binding));
        }

        void validate_variable(const VirtualVariable& variable) {
            if (variable.is_empty()) {
                throw std::logic_error("variable is invalid");
            }

            if (variable.variable_number() > stack_persistence_stage_.size()) {
                throw std::logic_error("variable number is larger than allocated stack space");
            }
        }

        void bind_to_system_register(VirtualVariable&& variable) {
            VirtualVariableSystemRegisterBinding&& binding = std::move(sys_register_stage_.dequeue_binding());
            apply_binding(std::move(variable), std::move(binding));
        }

        void load_variable_from_persistence(int variable_number) {
            // Only stage the variable if it isn't already there.
            if (!sys_register_stage_.is_staged(variable_number)) {
                VirtualVariable variable = stack_persistence_stage_.release(variable_number);

                bind_to_system_register(std::move(variable));
            }
        }

        void load_variable_from_persistence(arch::CpuRegister& sys_register, int variable_number) {
            if (!sys_register_stage_.is_staged(variable_number)) {
                VirtualVariable variable = stack_persistence_stage_.release(variable_number);

                bind_to_system_register(std::move(variable));
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
