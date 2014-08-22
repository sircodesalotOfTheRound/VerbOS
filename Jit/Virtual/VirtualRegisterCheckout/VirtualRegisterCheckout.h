//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "CpuRegister.h"
#include "VirtualRegister.h"

#ifndef __VirtualRegisterCheckout_H_
#define __VirtualRegisterCheckout_H_

namespace jit {
    class VirtualRegisterCheckout {
        const processor::CpuRegister& reg_;
        const VirtualRegister& virtual_register_;

    public:
        VirtualRegisterCheckout(const processor::CpuRegister& reg, const VirtualRegister& virtual_register) :
            reg_(reg), virtual_register_(virtual_register) {
        }

        const processor::CpuRegister& sys_register() const { return reg_; }
        const VirtualRegister& virtual_register() const { return virtual_register_; }
    };

    using ConstVirtualRegisterCheckout = const VirtualRegisterCheckout&;
}


#endif //__VirtualRegisterCheckout_H_
