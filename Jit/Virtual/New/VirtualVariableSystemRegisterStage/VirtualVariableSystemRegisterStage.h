//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <vector>
#include "VirtualVariableSystemRegisterBinding.h"
#include "OsxRegisters.h"
#include "SystemRegisterPriorityQueue.h"
#include "VirtualVariableCheckout.h"

#ifndef __VirtualVariableSystemRegisterStage_H_
#define __VirtualVariableSystemRegisterStage_H_

namespace jit {
    class VirtualVariableSystemRegisterStage {
        SystemRegisterPriorityQueue register_queue_;

    public:
        VirtualVariableSystemRegisterStage() {
            using namespace arch;
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(0, OsxRegisters::rax));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(1, OsxRegisters::rbx));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(2, OsxRegisters::rcx));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(3, OsxRegisters::rdx));

            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(4, OsxRegisters::rsi));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(5, OsxRegisters::rdi));

            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(6, OsxRegisters::r8));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(7, OsxRegisters::r9));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(8, OsxRegisters::r10));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(9, OsxRegisters::r11));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(10, OsxRegisters::r12));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(11, OsxRegisters::r13));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(12, OsxRegisters::r14));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(13, OsxRegisters::r15));
        }

        void with_register(int register_index, std::function<void(VirtualVariableCheckout)> callback) {
            /*VirtualRegisterBinding binding = checkout(register_index);
            VirtualRegisterCheckout register_checkout{binding.sys_register(), binding.virtual_register(), jit_opcodes};

            callback(register_checkout);

            release(register_index, binding);*/
        }

    };
}


#endif //__VirtualVariableSystemRegisterStage_H_
