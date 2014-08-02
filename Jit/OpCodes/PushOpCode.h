//
// Created by Reuben Kuhnert on 14-6-17.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//



#ifndef __PushOpCode_H_
#define __PushOpCode_H_

#include "OpCode.h"

namespace opcodes {
    class PushOpCode : public OpCode {
        Operand _operand;

    public:
        PushOpCode(sysarch::const_sys_register reg) : _operand(&reg) { }
        PushOpCode(int32 value) : _operand(value){ }

        size_t size() { return 5; }
        void render(jit::JitEmitter & writer);
    };
}


#endif //__PushOpCode_H_
