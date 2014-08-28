//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __VirtualVariableCheckout_H_
#define __VirtualVariableCheckout_H_

#include "VirtualVariable.h"
#include "CpuRegister.h"
#include "ProcessorOpCodeSet.h"

namespace jit {
    class VirtualVariableCheckout {
        op::ProcessorOpCodeSet& jit_opcodes_;
        arch::CpuRegister cpu_register_;
        const VirtualVariable& virtual_variable_;

    public:
        VirtualVariableCheckout(
            const arch::CpuRegister& sys_register,
            const VirtualVariable& virtual_variable):

            jit_opcodes_(jit_opcodes_),
            cpu_register_(sys_register),
            virtual_variable_(virtual_variable)
        {

        }

        int variable_number() const { return virtual_variable_.variable_number(); }

        op::ProcessorOpCodeSet& jit_opcodes() { return jit_opcodes_; }
        const arch::CpuRegister& sys_register() const { return cpu_register_; }
        const VirtualVariable& virtual_variable() const { return virtual_variable_; }
    };
}


#endif //__VirtualVariableCheckout_H_
