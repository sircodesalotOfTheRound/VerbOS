//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "CpuRegister.h"

#ifndef __SystemRegisterPriority_H_
#define __SystemRegisterPriority_H_

namespace jit {
    class SystemRegisterPriority {
        arch::CpuRegister register_;
        int priority_;
        int register_index_;

    public:
        SystemRegisterPriority(arch::CpuRegister& sys_register, int priority, int register_index)
            : register_(sys_register),
              priority_(priority),
              register_index_(register_index)
        {

        }

        arch::CpuRegister& sys_register() { return register_; }
        int priority() const { return priority_; }
        int register_index() const { return register_index_; }

        bool operator<(const SystemRegisterPriority& rhs) const {
            return priority_ < rhs.priority_;
        }
    };
}


#endif //__SystemRegisterPriority_H_
