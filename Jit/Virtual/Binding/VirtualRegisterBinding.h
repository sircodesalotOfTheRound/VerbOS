//
// Created by Reuben Kuhnert on 14/8/21.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __VirtualRegisterAllocation_H_
#define __VirtualRegisterAllocation_H_

#include "CpuRegister.h"
#include "VirtualRegister.h"

namespace jit {
    class VirtualRegisterBinding {
        const processor::CpuRegister &register_;

        int priority_;
        VirtualRegister virtual_register_;

    public:
        VirtualRegisterBinding(const processor::CpuRegister &sys_register) :
            register_(sys_register),
            virtual_register_(VirtualRegister::EMPTY)
        {

        }

        bool operator<<(const VirtualRegisterBinding &rhs) const {
            return virtual_register_.priority() < rhs.virtual_register().priority();
        }

        VirtualRegister virtual_register() const { return virtual_register_; }

        void bind(VirtualRegister virtual_register) {
            virtual_register_ = virtual_register;
        }
    };
}

#endif //__VirtualRegisterAllocation_H_
