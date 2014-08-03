//
// Created by Reuben Kuhnert on 14-6-19.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "SystemRegister.h"
#include "OpCode.h"

#ifndef ADD_OP_CODE
#define ADD_OP_CODE


namespace opcodes {
    class AddOpCode : public OpCode {
        Operand _lhs;
        Operand _rhs;

    public:
        AddOpCode(sysarch::const_sys_register lhs,sysarch::const_sys_register rhs) : _lhs(&lhs), _rhs(&rhs) { }
        AddOpCode(sysarch::const_sys_register lhs, uint64 rhs) : _lhs(&lhs), _rhs(rhs) { }

        size_t size() { return -1; }
        void render(jit::JitEmitter & writer);
    };
}


#endif //__AddOpCode_H_
