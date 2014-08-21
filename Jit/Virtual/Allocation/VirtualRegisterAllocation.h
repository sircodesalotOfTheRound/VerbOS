//
// Created by Reuben Kuhnert on 14/8/21.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "CpuRegister.h"
#include "VirtualRegister.h"

#ifndef __VirtualRegisterAllocation_H_
#define __VirtualRegisterAllocation_H_

namespace jit {
    class VirtualRegisterAllocation {
        const processor::CpuRegister &register_;

        int priority_;
        VirtualRegister allocation_;

    public:
        VirtualRegisterAllocation(const processor::CpuRegister &reg) : register_(reg),
            allocation_(VirtualRegister::EMPTY)
        {

        }

        bool operator<<(const VirtualRegisterAllocation &rhs) const { return priority_ < rhs.priority_; }

        int priority() const { return priority_; }
        void priority(int value) { priority_ = value; }
    };
}

#endif //__VirtualRegisterAllocation_H_
