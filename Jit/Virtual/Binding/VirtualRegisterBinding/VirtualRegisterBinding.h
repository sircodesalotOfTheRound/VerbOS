//
// Created by Reuben Kuhnert on 14/8/21.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef VIRTUAL_REGISTER_BINDING_H
#define VIRTUAL_REGISTER_BINDING_H

#include "CpuRegister.h"
#include "VirtualRegister.h"

namespace jit {
    class VirtualRegisterBinding {
        const static int IS_FREE = -1;
        arch::CpuRegister sys_register_;

        int bound_register_number_;
        VirtualRegister virtual_register_;

    public:
        VirtualRegisterBinding(const arch::CpuRegister &sys_register) :
            sys_register_(sys_register),
            virtual_register_(VirtualRegister::EMPTY),
            bound_register_number_(IS_FREE)
        {

        }

        bool operator>(const VirtualRegisterBinding &rhs) const {
            return rhs.priority() > priority();
        }

        const arch::CpuRegister& sys_register() const { return sys_register_; }
        VirtualRegister& virtual_register() { return virtual_register_; }
        int priority() const { return virtual_register_.priority(); }

        void bind(int bound_register_number, VirtualRegister virtual_register) {
            bound_register_number_ = bound_register_number;
            virtual_register_ = virtual_register;
        }

        int bound_register_number() const { return bound_register_number_; }

        void clear() {
            virtual_register_ = VirtualRegister::EMPTY;
            bound_register_number_ = IS_FREE;
        }

        bool is_empty() { return bound_register_number_ == IS_FREE; }

    };

    using ConstVirtualRegisterBindingRef = const VirtualRegisterBinding&;
}

#endif //VIRTUAL_REGISTER_BINDING_H
