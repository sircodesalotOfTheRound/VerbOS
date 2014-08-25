//
// Created by Reuben Kuhnert on 14/8/25.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VirtualRegisterBinding.h"

#ifndef __VirtualRegisterBindingTable_H_
#define __VirtualRegisterBindingTable_H_

namespace jit {
    class VirtualRegisterBindingTable {
        // We want to be able to quickly search by both virtual-register, and system-register.
        std::unordered_map<int, VirtualRegisterBinding> virtual_register_bindings;
        std::unordered_map <arch::CpuRegister, VirtualRegisterBinding> cpu_register_bindings;

    public:
        bool is_bound(int virtual_register_number) {
            return virtual_register_bindings.find(virtual_register_number) != virtual_register_bindings.end();
        }

        bool is_bound(arch::ConstCpuRegisterRef cpu_register) {
            return cpu_register_bindings.find(cpu_register) != cpu_register_bindings.end();
        }

        void insert_binding(ConstVirtualRegisterBindingRef binding) {
            int virtual_register_number = binding.bound_register_number();
            auto& cpu_register = binding.sys_register();

            virtual_register_bindings.insert({ virtual_register_number, binding });
            cpu_register_bindings.insert({ cpu_register, binding });
        }

        VirtualRegisterBinding& operator[](arch::ConstCpuRegisterRef reg) {
            return cpu_register_bindings.at(reg);
        }

        VirtualRegisterBinding& operator[](int virtual_register_index) {
            return virtual_register_bindings.at(virtual_register_index);
        }

        void remove_binding(ConstVirtualRegisterBindingRef binding) {
            remove_binding(binding.bound_register_number());
        }

        void remove_binding(int virtual_register_index) {
            // Find the binding by virtual register number.
            auto virutual_register_binding_iterator = virtual_register_bindings.find(virtual_register_index);
            auto binding = *virutual_register_binding_iterator;

            auto cpu_register = binding.second.sys_register();
            auto cpu_register_binding_iterator = cpu_register_bindings.find(cpu_register);

            // Erase
            virtual_register_bindings.erase(virutual_register_binding_iterator);
            cpu_register_bindings.erase(cpu_register_binding_iterator);
        }

        void remove_binding(arch::ConstCpuRegisterRef reg) {
            // Find the binding by cpu register.
            auto cpu_register_binding_iterator = cpu_register_bindings.find(reg);
            auto binding = *cpu_register_binding_iterator;

            auto virtual_register_number = binding.second.bound_register_number();
            auto virutual_register_binding_iterator = virtual_register_bindings.find(virtual_register_number);

            // Erase
            virtual_register_bindings.erase(virutual_register_binding_iterator);
            cpu_register_bindings.erase(cpu_register_binding_iterator);
        }


    private:
    };
}


#endif //__VirtualRegisterBindingTable_H_
