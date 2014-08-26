//
// Created by Reuben Kuhnert on 14/8/25.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VirtualRegisterBindingPriorityQueue_H_
#define __VirtualRegisterBindingPriorityQueue_H_

#include <set>
#include <map>
#include "VirtualRegisterBinding.h"
#include "OsxRegisters.h"

namespace jit {
    class VirtualRegisterBindingPriorityQueue {
        struct VirtualRegisterBindingComparator {
            bool operator()(const VirtualRegisterBinding& lhs, const VirtualRegisterBinding& rhs) {
                return lhs.priority() < rhs.priority();
            }
        };

    public:
        VirtualRegisterBinding pop() {
            VirtualRegisterBinding binding = *queue_.begin();

            register_map_.erase(register_map_.find(binding.sys_register()));
            queue_.erase(queue_.begin());

            return binding;
        }

        VirtualRegisterBinding pop(arch::ConstCpuRegisterRef cpu_register) {
            auto register_map_iterator = register_map_.find(cpu_register);
            VirtualRegisterBinding binding = register_map_iterator->second;

            auto found_iter = std::find_if(queue_.begin(), queue_.end(),
                [&](const VirtualRegisterBinding& item) {

                return item.sys_register() == cpu_register;
            });

            queue_.erase(found_iter);
            register_map_.erase(register_map_iterator);

            return binding;
        }

        void push(VirtualRegisterBinding binding) {
            queue_.insert(binding);
            register_map_.insert({ binding.sys_register(), binding });
        }

        bool is_empty() { return queue_.empty(); }

    private:

        std::multiset<VirtualRegisterBinding, VirtualRegisterBindingComparator> queue_;
        std::unordered_map<arch::CpuRegister, VirtualRegisterBinding> register_map_;
    };
}


#endif //__VirtualRegisterBindingPriorityQueeu_H_
