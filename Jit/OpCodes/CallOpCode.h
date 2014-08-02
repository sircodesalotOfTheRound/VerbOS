//
// Created by Reuben Kuhnert on 14-6-17.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "OpCode.h"

#ifndef __CallOpCode_H_
#define __CallOpCode_H_

namespace opcodes {
    class CallOpCode : public OpCode {
        Operand _operand;

    public:
        CallOpCode(sysarch::p_sys_register reg) : _operand(reg) { }
        CallOpCode(void* location) : _operand(location) { }

        size_t size() override { return -1; }
        void render(jit::JitEmitter & writer);
    };
}


#endif //__CallOpCode_H_
