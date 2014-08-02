//
// Created by Reuben Kuhnert on 14-6-11.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "OpCode.h"

#ifndef __MovOpCode_H_
#define __MovOpCode_H_

namespace opcodes {
    class MovOpCode : public OpCode {
        Operand _lhs;
        Operand _rhs;

    public:
        MovOpCode(sysarch::const_sys_register lhs, const uint64 value)
            : _lhs(&lhs), _rhs(value) { }

        MovOpCode(sysarch::const_sys_register lhs,sysarch::const_sys_register rhs)
            : _lhs(&lhs), _rhs(&rhs) { }

        MovOpCode(void* lhs,sysarch::p_sys_register rhs)
            : _lhs(lhs), _rhs(rhs) {
        }

        size_t size() { return 5; }
        void render(jit::JitEmitter & writer);
    };
}


#endif //__MovOpCode_H_
