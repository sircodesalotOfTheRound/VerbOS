//
// Created by Reuben Kuhnert on 14-6-18.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//



#ifndef __SyscallOpCode_H_
#define __SyscallOpCode_H_

#include "OpCode.h"

class SyscallOpCode : public opcodes::OpCode {
public:
    size_t size() { return 2; }
    void render(jit::JitEmitter & writer) {
        writer.write_opcode(0x0f);
        writer.write_opcode(0x05);
    }
};


#endif //__SyscallOpCode_H_
