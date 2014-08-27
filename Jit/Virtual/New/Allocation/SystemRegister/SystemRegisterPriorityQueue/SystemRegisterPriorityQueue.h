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
        bool queue_invalidated_;

        std::vector<VirtualVariableSystemRegisterBinding> bindings_;
        std::unordered_map<arch::CpuRegister, int> register_map_;
        std::unordered_map<int, int> bound_variable_map_;
        std::priority_queue<SystemRegisterPriority> queue_;

    public:
        SystemRegisterPriorityQueue() :
            queue_invalidated_(true)
        {
            bindings_.reserve(15);
        }

        void insert_system_register_binding(VirtualVariableSystemRegisterBinding &&binding)  {
            register_map_.insert({ binding.sys_register(), binding.binding_number() });
            bindings_.push_back(std::move(binding));

            queue_invalidated_ = true;
        }

        bool is_bound(const VirtualVariable& variable) {
            return is_bound(variable.variable_number());
        }

        bool is_bound(int virtual_variable_number) {
            return bound_variable_map_.find(virtual_variable_number) != bound_variable_map_.end();
        }

        bool is_bound(const arch::CpuRegister& sys_register) {
            int register_index = index_from_cpu_register(sys_register);

            return bindings_[register_index].contains_variable();
        }

        arch::CpuRegister get_variable_register(int virtual_variable_number) {
            return borrow(virtual_variable_number).sys_register();
        }

        VirtualVariableCheckout borrow(int virtual_variable_number) {
            if (!is_bound(virtual_variable_number)) {
                throw std::logic_error("variable is not bound to a register");
            }

            VirtualVariableSystemRegisterBinding& binding = get_binding(virtual_variable_number);
            return VirtualVariableCheckout (binding.sys_register(), binding.variable());
        }

        void bind(VirtualVariable&& variable) {
            VirtualVariableSystemRegisterBinding& binding = dequeue();

            binding.bind_variable(variable.variable_number(), std::move(variable));
            bound_variable_map_.insert( {binding.virtual_variable_number(), binding.binding_number() });
        }

        void bind(const arch::CpuRegister& cpu_register, VirtualVariable&& variable) {
            if (variable.is_empty()) {
                throw std::logic_error("variable content is empty. is it already bound?");
            }

            if (is_bound(variable.variable_number())) {
               throw std::logic_error("variable is already bound");
            }

            VirtualVariableSystemRegisterBinding& binding = dequeue(cpu_register);

            binding.bind_variable( variable.variable_number(), std::move(variable));
            bound_variable_map_.insert( { variable.variable_number(), binding.binding_number() });
        }

        VirtualVariable&& unbind(int virtual_variable_number) {
            if (!is_bound(virtual_variable_number)) {
                throw std::logic_error("variable is not bound");
            }

            return std::move(release(virtual_variable_number));
        }

    private:

        VirtualVariable&& release(int virtual_register_index) {
            VirtualVariableSystemRegisterBinding& binding = get_binding(virtual_register_index);

            // Delete from bound variable map.
            bound_variable_map_.erase(bound_variable_map_.find(virtual_register_index));

            // Delete from register map
            register_map_.erase(register_map_.find(binding.sys_register()));

            // return the variable.
            VirtualVariable variable = std::move(binding.variable());
            return std::move(variable);
        }

        int index_from_cpu_register(const arch::CpuRegister& sys_register) {
            return register_map_.at(sys_register);
        }

        VirtualVariableSystemRegisterBinding& get_binding(int virtual_register_number) {
            auto binding_number_iter = bound_variable_map_.find(virtual_register_number);

            if (binding_number_iter == bound_variable_map_.end()) {
                throw std::logic_error("variable is not bound");
            }

            return bindings_[binding_number_iter->second];
        }

        VirtualVariableSystemRegisterBinding& dequeue() {
            if (queue_invalidated_) {
                prioritize();
            }

            // Pop item from queue
            const SystemRegisterPriority& priority = queue_.top();
            queue_.pop();

            VirtualVariableSystemRegisterBinding& binding = bindings_[priority.register_index()];
            return binding;
        }

        VirtualVariableSystemRegisterBinding& dequeue(const arch::CpuRegister& sys_register) {
            int sys_register_index = index_from_cpu_register(sys_register);

            if (bindings_[sys_register_index].contains_variable()) {
                throw std::logic_error("register must be cleared before it can be reused");
            }

            queue_invalidated_ = true;
            return bindings_[sys_register_index];
        }

        void prioritize() {
            queue_ = std::priority_queue<SystemRegisterPriority>();

            for (auto& binding : bindings_) {
                SystemRegisterPriority priority(binding.sys_register(), binding.priority(), binding.binding_number());
                queue_.push(priority);
            }
        }
    };
}


#endif //__SystemRegisterPriorityQueue_H_
