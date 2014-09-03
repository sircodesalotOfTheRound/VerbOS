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
    class OsxSystemRegisterPriorityQueue : public SystemRegisterPriorityQueue {

    public:
        OsxSystemRegisterPriorityQueue()
        {
            using namespace arch;
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(0, OsxRegisters::rax));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(1, OsxRegisters::rbx));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(2, OsxRegisters::rcx));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(3, OsxRegisters::rdx));

            insert_system_register_binding(VirtualVariableSystemRegisterBinding(4, OsxRegisters::rsi));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(5, OsxRegisters::rdi));

            insert_system_register_binding(VirtualVariableSystemRegisterBinding(6, OsxRegisters::r8));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(7, OsxRegisters::r9));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(8, OsxRegisters::r10));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(9, OsxRegisters::r11));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(10, OsxRegisters::r12));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(11, OsxRegisters::r13));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(12, OsxRegisters::r14));
            insert_system_register_binding(VirtualVariableSystemRegisterBinding(13, OsxRegisters::r15));
        }
    };
}


#endif //__VirtualVariableSystemRegisterStage_H_
