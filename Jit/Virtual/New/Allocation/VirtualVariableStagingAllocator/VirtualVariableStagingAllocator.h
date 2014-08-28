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
            : stack_persistence_stage_(size)
        {

        }

        void bind_to_stack_persistence(VirtualVariable &&variable) {
            stack_persistence_stage_.persist_variable(std::move(variable));

            VirtualVariable&& var = stack_persistence_stage_.release(2);
            std::cout << var.type() << std::endl;
        }

        void bind_to_system_register(VirtualVariable &&variable) {
            VirtualVariableSystemRegisterBinding&& binding = std::move(sys_register_stage_.dequeue_binding());

            if (binding.contains_variable()) {
                VirtualVariable&& released_variable = binding.release_variable();
                stack_persistence_stage_.persist_variable(std::move(released_variable));
            }

            binding.bind_variable(std::move(variable));
            sys_register_stage_.bind(std::move(binding));
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
        void load_variable_from_persistence(int variable_number) {
            // Only stage the variable if it isn't already there.
            if (!sys_register_stage_.is_bound(variable_number)) {
                VirtualVariable variable = stack_persistence_stage_.release(variable_number);

                bind_to_system_register(std::move(variable));
            }
        }
    };
}


#endif //__VirtualVariableStagingAllocator_H_
