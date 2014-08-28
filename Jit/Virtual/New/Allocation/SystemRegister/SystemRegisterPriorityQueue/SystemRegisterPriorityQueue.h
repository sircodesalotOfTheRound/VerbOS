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
            queue_invalidated_(true)
        {
            bindings_.reserve(15);
        }

        iterator begin() { return bindings_.begin(); }
        iterator end() { return bindings_.end(); }

        void insert_system_register_binding(VirtualVariableSystemRegisterBinding &&binding)  {
            register_map_.insert({ binding.sys_register(), binding.binding_number() });
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

        VirtualVariableSystemRegisterBinding&& dequeue_binding() {
            VirtualVariableSystemRegisterBinding&& binding = std::move(dequeue());
            return std::move(binding);
        }

        VirtualVariableSystemRegisterBinding&& dequeue_binding(const arch::CpuRegister& sys_register) {
            VirtualVariableSystemRegisterBinding&& binding = std::move(dequeue(sys_register));
            return std::move(binding);
        }

        void bind(VirtualVariableSystemRegisterBinding&& binding) {
            VirtualVariable& variable = binding.variable();
            validate_variable(variable);

            // Insert the binding into the lookup.
            bind_metadata(binding);

            // Reinsert the binding
            bindings_[binding.binding_number()] = std::move(binding);

            queue_invalidated_ = true;
        }

        // Temporary deprecation!
        void bind(const arch::CpuRegister& cpu_register, VirtualVariable&& variable) {
            validate_variable(variable);

            VirtualVariableSystemRegisterBinding& binding = dequeue(cpu_register);
            binding.bind_variable(std::move(variable));

            bind_metadata(binding);
        }

        VirtualVariable&& unbind(int virtual_variable_number) {
            if (!is_bound(virtual_variable_number)) {
                throw std::logic_error("variable is not bound");
            }

            return std::move(release(virtual_variable_number));
        }

    private:
        void validate_variable(const VirtualVariable& variable) {
            if (variable.is_empty()) {
                throw std::logic_error("variable content is empty. is it already bound?");
            }

            if (is_bound(variable.variable_number())) {
               throw std::logic_error("variable is already bound");
            }
        }

        // Remove information used to look up this variable (since it's no
        // longer bound to a physical register).
        void remove_metadata(VirtualVariableSystemRegisterBinding& binding) {
            // Erase from register lookup.
            register_map_.erase(register_map_.find(binding.sys_register()));

            // Erase from bound variable map.
            bound_variable_map_.erase(bound_variable_map_.find(binding.variable_number()));
        }

        void bind_metadata(VirtualVariableSystemRegisterBinding& binding);

        VirtualVariable && release(int virtual_register_index);

        int register_index_from_cpu_register(const arch::CpuRegister &sys_register);

        VirtualVariableSystemRegisterBinding & get_binding(int virtual_register_number);

        VirtualVariableSystemRegisterBinding && dequeue();

        VirtualVariableSystemRegisterBinding & dequeue(const arch::CpuRegister& sys_register);

        void prioritize();
    };
}


#endif //__SystemRegisterPriorityQueue_H_
