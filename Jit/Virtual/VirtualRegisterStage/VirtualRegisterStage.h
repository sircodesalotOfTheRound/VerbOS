//
// Created by Reuben Kuhnert on 14/8/21.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VirtualRegisterStage_H_
#define __VirtualRegisterStage_H_

#include <vector>
#include "VirtualRegisterBinding.h"

namespace jit {
    class VirtualRegisterStage {
        std::array<VirtualRegister, 256> registers_;

    public:
        VirtualRegister& operator[](int index) { return registers_[index]; }
    };
}


#endif //__VirtualRegisterStage_H_
