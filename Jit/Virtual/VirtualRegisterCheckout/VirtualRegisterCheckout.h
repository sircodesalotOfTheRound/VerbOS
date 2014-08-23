//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "CpuRegister.h"
#include "VirtualRegister.h"
#include "ProcessorOpCodeSet.h"

#ifndef __VirtualRegisterCheckout_H_
#define __VirtualRegisterCheckout_H_

namespace jit {
    class VirtualRegisterCheckout {
        const arch::CpuRegister& reg_;
        const VirtualRegister& virtual_register_;
        op::ProcessorOpCodeSet& opcodes_;

    public:
        VirtualRegisterCheckout(const arch::CpuRegister& reg,
                const VirtualRegister& virtual_register,
                op::ProcessorOpCodeSet& opcodes) :
            reg_(reg),
            virtual_register_(virtual_register),
            opcodes_(opcodes)
        {

        }

        const arch::CpuRegister& sys_register() const { return reg_; }
        const VirtualRegister& virtual_register() const { return virtual_register_; }
        op::ProcessorOpCodeSet& opcodes() { return opcodes_; }
    };

    using VirtualRegisterCheckoutRef = VirtualRegisterCheckout&;
}


#endif //__VirtualRegisterCheckout_H_
