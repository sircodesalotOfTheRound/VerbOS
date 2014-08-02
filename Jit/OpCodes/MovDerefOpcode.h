//
// Created by Reuben Kuhnert on 14-6-18.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#ifndef MOV_DEREF_OPCODE_H
#define MOV_DEREF_OPCODE_H

#include "OpCode.h"

namespace opcodes {
    class MovDerefOpcode : public OpCode {
    public:
        enum DEREF {
            DEREF_SOURCE,
            DEREF_DESTINATION
        };

        MovDerefOpcode(sysarch::const_sys_register lhs, sysarch::const_sys_register rhs, DEREF dereference)
            : lhs_(&lhs), rhs_(&rhs), dereference_(dereference), offset_(0)
        {

        }

        MovDerefOpcode(sysarch::const_sys_register lhs, sysarch::const_sys_register rhs, DEREF dereference, off_t offset)
            : lhs_(&lhs), rhs_(&rhs), dereference_(dereference), offset_(offset)
        {

        }

        virtual size_t size() { return -1; }
        virtual void render(jit::JitEmitter & writer);

    private:
        off_t offset_;
        DEREF dereference_;
        Operand lhs_;
        Operand rhs_;
    };
}

#endif //__MovDerefOpcode_H_
