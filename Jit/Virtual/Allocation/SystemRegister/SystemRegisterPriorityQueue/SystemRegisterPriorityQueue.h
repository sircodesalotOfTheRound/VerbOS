//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __SystemRegisterPriorityQueue_H_
#define __SystemRegisterPriorityQueue_H_

#include <queue>
#include "VirtualVariableSystemRegisterBinding.h"
#import "SystemRegisterPriority.h"
#include "VirtualVariableCheckout.h"

namespace jit {
    class SystemRegisterPriorityQueue {
        using iterator = std::vector<VirtualVariableSystemRegisterBinding>::iterator;

        bool queue_invalidated_;

        std::vector<VirtualVariableSystemRegisterBinding> bindings_;
        std::unordered_map<arch::CpuRegister, int> register_map_;
        std::unordered_map<int, int> bound_variable_map_;
        std::priority_queue<SystemRegisterPriority> queue_;

    public:
        SystemRegisterPriorityQueue() :
            queue_invalidated_(true) {
        }

        size_t size() { return bindings_.size(); }

        void insert_system_register_binding(VirtualVariableSystemRegisterBinding&& binding) {
            register_map_.insert({binding.sys_register(), binding.binding_number()});
            bindings_.push_back(std::move(binding));

        }

        // Binding checks
        bool is_bound(const VirtualVariable& variable) {
            return is_bound(variable.variable_number());
        }

        bool is_bound(int virtual_variable_number) {
            return bound_variable_map_.find(virtual_variable_number) != bound_variable_map_.end();
        }

        bool is_bound(const arch::CpuRegister& sys_register) {
            int register_index = register_index_from_cpu_register(sys_register);

            return bindings_[register_index].contains_variable();
        }

        VirtualVariableSystemRegisterBinding&& dequeue_binding() {
            VirtualVariableSystemRegisterBinding&& binding = std::move(dequeue());

            return std::move(binding);
        }

        // Release binding
        VirtualVariableSystemRegisterBinding&& release(int binding_number) {
            VirtualVariableSystemRegisterBinding&& binding = std::move(bindings_[binding_number]);

            remove_metadata(binding);
            return std::move(binding);
        }

        void with_binding_by_register(arch::CpuRegister sys_register,
            std::function<void(VirtualVariableSystemRegisterBinding& register_binding)> callback) {

            // Release.
            VirtualVariableSystemRegisterBinding&& binding = std::move(dequeue(sys_register));

            // Perform task.
            callback(binding);

            // Then rebind.
            bind(std::move(binding));
        }

        void with_binding_by_bindnum(int binding_number,
            std::function<void(VirtualVariableSystemRegisterBinding& register_binding)> callback) {

            // Release.
            VirtualVariableSystemRegisterBinding&& binding = std::move(release(binding_number));

            // Perform task.
            callback(binding);

            // Then rebind.
            bind(std::move(binding));
        }

        void with_binding_by_varnum(int variable_number,
            std::function<void(VirtualVariableSystemRegisterBinding& register_binding)> callback) {

            // Release.
            VirtualVariableSystemRegisterBinding&& binding = std::move(dequeue(variable_number));

            // Perform task.
            callback(binding);

            // Then rebind.
            bind(std::move(binding));
        }

        void with_binding_by_availability(std::function<void(VirtualVariableSystemRegisterBinding& register_binding)> callback) {
            // Release.
            VirtualVariableSystemRegisterBinding&& binding = std::move(dequeue());

            // Perform task.
            callback(binding);

            // Then rebind.
            bind(std::move(binding));
        }


        void bind(VirtualVariableSystemRegisterBinding&& binding) {
            if (binding.contains_variable()) {
                validate_variable(binding.variable());
                binding.increment_usage_count();
            }

            // Insert the binding into the lookup.
            bind_metadata(binding);

            // Add to the priority queue
            SystemRegisterPriority priority (binding);
            queue_.push(priority);

            // Reinsert the binding
            bindings_[binding.binding_number()] = std::move(binding);
        }

        VirtualVariable& borrow_variable(int variable_number) {
            if (is_bound(variable_number)) {
                int binding_number = bound_variable_map_.at(variable_number);
                return bindings_[binding_number].variable();
            }

            throw std::logic_error("variable is not staged to a register");
        }


    private:
        void validate_variable(const VirtualVariable& variable) {
            if (variable.is_empty()) {
                throw std::logic_error("variable content is empty. is it already bound?");
            }
        }

        // Remove information used to look up this variable (since it's no
        // longer bound to a physical register).
        void remove_metadata(VirtualVariableSystemRegisterBinding& binding) {
            // Erase the system-register to binding mapping.
            register_map_.erase(register_map_.find(binding.sys_register()));

            // Erase from bound variable map (only if there is a bound variable).
            if (binding.contains_variable()) {
                bound_variable_map_.erase(bound_variable_map_.find(binding.variable_number()));
            }
        }

        void bind_metadata(VirtualVariableSystemRegisterBinding& binding);

        int register_index_from_cpu_register(const arch::CpuRegister& sys_register);

        VirtualVariableSystemRegisterBinding&& dequeue();

        VirtualVariableSystemRegisterBinding&& dequeue(int variable_number);

        VirtualVariableSystemRegisterBinding&& dequeue(const arch::CpuRegister& sys_register);

        void prioritize();
    };
}


#endif //__SystemRegisterPriorityQueue_H_
