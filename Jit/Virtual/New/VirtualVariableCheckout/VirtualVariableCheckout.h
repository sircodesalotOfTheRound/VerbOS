//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VirtualVariable.h"
#include "CpuRegister.h"

#ifndef __VirtualVariableCheckout_H_
#define __VirtualVariableCheckout_H_

namespace jit {
    class VirtualVariableCheckout {
        arch::CpuRegister cpu_register_;
        const VirtualVariable& virtual_variable_;

    public:
        VirtualVariableCheckout(const arch::CpuRegister& sys_register,
                const VirtualVariable& virtual_variable):
            cpu_register_(sys_register),
            virtual_variable_(virtual_variable)
        {

        }

        int variable_number() const { return virtual_variable_.variable_number(); }
        const arch::CpuRegister& sys_register() const { return cpu_register_; }
        const VirtualVariable& virtual_variable() const { return virtual_variable_; }
    };
}


#endif //__VirtualVariableCheckout_H_
