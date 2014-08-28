//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VirtualVariableSystemRegisterStage.h"
#include "VirtualVariableStackPersistenceStage.h"

#ifndef __VirtualVariableStagingAllocator_H_
#define __VirtualVariableStagingAllocator_H_

namespace jit {
    class VirtualVariableStagingAllocator {
        VirtualVariableStackPersistenceStage stack_persistence_stage_;
        VirtualVariableSystemRegisterStage sys_register_stage_;

    public:
        VirtualVariableStagingAllocator(size_t size)
            : stack_persistence_stage_(size) {

        }

        void stack_persist(VirtualVariable &&variable) {
            validate_variable(variable);

            stack_persistence_stage_.persist_variable(std::move(variable));
        }

        void show() {
            sys_register_stage_.show();
        }

        void bind_to_system_register(const arch::CpuRegister &sys_register, int variable_index) {
            // If the variable is on the stack, then load it and bind it to the register
            if (stack_persistence_stage_.contains_variable(variable_index)) {
                VirtualVariable &&variable = stack_persistence_stage_.release(variable_index);
                VirtualVariableSystemRegisterBinding&& binding
                    = std::move(sys_register_stage_.dequeue_binding(sys_register));

                apply_binding(std::move(variable), std::move(binding));
            }
            else if (sys_register_stage_.is_bound(variable_index)) {
                VirtualVariable&& variable = std::move(sys_register_stage_.unbind(variable_index));

                VirtualVariableSystemRegisterBinding&& binding
                    = std::move(sys_register_stage_.dequeue_binding(sys_register));

                // If something is already stored in the binding, persist it.
                if (binding.contains_variable()) {
                    //stack_persist(std::move(binding.release_variable()));
                }

                apply_binding(std::move(variable), std::move(binding));

            } else {
                // If the variable isn't anywhere, then throw an exception.
                throw std::logic_error("variable is not yet associated");
            }
        }
        
        void bind_to_system_register(VirtualVariable &&variable) {
            VirtualVariableSystemRegisterBinding &&binding = std::move(sys_register_stage_.dequeue_binding());

            apply_binding(std::move(variable), std::move(binding));
        }

        void with_register(int virtual_register_number, std::function<void(VirtualVariableCheckout &)> callback) {
            // Ensure the variable is staged.
            load_variable_from_persistence(virtual_register_number);

            sys_register_stage_.with_register(virtual_register_number, callback);
        }

        void with_register(int lhs_register_number, int rhs_register_number,
                std::function<void(VirtualVariableCheckout &, VirtualVariableCheckout &)> callback) {

            // Ensure the variables are staged.
            load_variable_from_persistence(lhs_register_number);
            load_variable_from_persistence(rhs_register_number);

            sys_register_stage_.with_register(lhs_register_number, rhs_register_number, callback);
        }

    private:
        void apply_binding(VirtualVariable &&variable, VirtualVariableSystemRegisterBinding &&binding) {
            validate_variable(variable);

            if (binding.contains_variable()) {
                VirtualVariable &&released_variable = binding.release_variable();
                stack_persistence_stage_.persist_variable(std::move(released_variable));
            }

            binding.bind_variable(std::move(variable));
            sys_register_stage_.bind(std::move(binding));
        }

        void validate_variable(const VirtualVariable &variable) {
            if (variable.is_empty()) {
                throw std::logic_error("variable is invalid");
            }

            if (variable.variable_number() > stack_persistence_stage_.size()) {
                throw std::logic_error("variable number is larger than allocated stack space");
            }
        }

        void load_variable_from_persistence(int variable_number) {
            // Only stage the variable if it isn't already there.
            if (!sys_register_stage_.is_bound(variable_number)) {
                VirtualVariable variable = stack_persistence_stage_.release(variable_number);

                bind_to_system_register(std::move(variable));
            }
        }

        void load_variable_from_persistence(arch::CpuRegister &sys_register, int variable_number) {
            if (!sys_register_stage_.is_bound(variable_number)) {
                VirtualVariable variable = stack_persistence_stage_.release(variable_number);

                bind_to_system_register(std::move(variable));
            }
        }
    };
}


#endif //__VirtualVariableStagingAllocator_H_
