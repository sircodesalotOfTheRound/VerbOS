//
// Created by Reuben Kuhnert on 14-6-19.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "SystemRegister.h"
#include "OpCode.h"

#ifndef SUB_OP_CODE
#define SUB_OP_CODE


namespace opcodes {
    class SubOpCode : public OpCode {
        Operand _lhs;
        Operand _rhs;

    public:
        SubOpCode( sysarch::const_sys_register lhs, sysarch::const_sys_register rhs) : _lhs(&lhs), _rhs(&rhs) { }
        SubOpCode( sysarch::const_sys_register reg, uint64_t size) : _lhs(&reg), _rhs(size) { }

        size_t size() { return -1; }
        void render(jit::JitEmitter & writer);
    };
}


#endif //__AddOpCode_H_
