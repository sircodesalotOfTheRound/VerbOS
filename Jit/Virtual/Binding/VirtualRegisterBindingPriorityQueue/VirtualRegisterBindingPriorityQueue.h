//
// Created by Reuben Kuhnert on 14/8/25.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VirtualRegisterBindingPriorityQueeu_H_
#define __VirtualRegisterBindingPriorityQueeu_H_

#include <set>
#include <map>
#include "VirtualRegisterBinding.h"

namespace jit {
    class VirtualRegisterBindingPriorityQueue {
        std::unordered_map<arch::CpuRegister, VirtualRegisterBinding> register_map_;
        std::multiset<VirtualRegisterBinding, std::greater<VirtualRegisterBinding>> queue_;

    public:
        VirtualRegisterBinding pop() {
            auto binding_iterator = queue_.begin();
            auto binding = *binding_iterator;

            auto register_map_iterator = register_map_.find(binding.sys_register());

            register_map_.erase(register_map_iterator);
            queue_.erase(binding_iterator);

            return binding;
        }

        VirtualRegisterBinding pop(arch::ConstCpuRegisterRef cpu_register) {
            auto register_map_iterator = register_map_.find(cpu_register);
            auto binding = register_map_iterator->second;

            auto set_iterator = queue_.find(binding);
            queue_.erase(set_iterator);
            register_map_.erase(register_map_iterator);

            return binding;
        }

        void push(VirtualRegisterBinding binding) {
            queue_.insert(binding);
            register_map_.insert({ binding.sys_register(), binding });
        }
    };
}


#endif //__VirtualRegisterBindingPriorityQueeu_H_
