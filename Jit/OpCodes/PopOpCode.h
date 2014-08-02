//
// Created by Reuben Kuhnert on 14-6-17.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "OpCode.h"

#ifndef __PopOpCode_H_
#define __PopOpCode_H_

namespace opcodes {
    class PopOpCode : public OpCode {
        Operand _operand;

    public:
        PopOpCode(sysarch::const_sys_register const reg) : _operand(&reg) { }

        size_t size() override { return 5; }
        void render(jit::JitEmitter & writer);
    };
}


#endif //__PopOpCode_H_
