//
// Created by Reuben Kuhnert on 14-6-18.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#ifndef JITCODESEGMENT_H
#define JITCODESEGMENT_H

#include <vector>
#include "OpCode.h"
#include "../OpCodes/PushOpCode.h"
#include "../OpCodes/PopOpCode.h"
#include "../OpCodes/CallOpCode.h"
#include "../OpCodes/ReturnOpCode.h"
#include "../OpCodes/MovOpCode.h"
#include "../OpCodes/MovDerefOpcode.h"
#include "../OpCodes/AddOpCode.h"
#include "../OpCodes/SubOpCode.h"
#include "SyscallOpCode.h"
#include "JitEmitter.h"
#include "CallStub.h"
#import "SystemRegister.h"
#include "Osx64Registers.h"

namespace jit {
    using namespace opcodes;

    class JitCodeSegment {
        std::vector<OpCode*> _opcodes;
        void add_opcode(OpCode *opcode) { _opcodes.push_back(opcode); }

        // Todo: Fix this hardcode later.
        sysarch::Osx64Registers registers_;

    public:
        JitCodeSegment();
        ~JitCodeSegment();

        void add(sysarch::const_sys_register lhs, uint64 rhs);
        void add(sysarch::const_sys_register lhs,sysarch::const_sys_register rhs);

        void sub(sysarch::const_sys_register lhs, sysarch::const_sys_register rhs);
        void sub(sysarch::const_sys_register lhs, uint64_t size);

        void push(sysarch::const_sys_register reg);
        void push(int32 value);
        void pop(sysarch::const_sys_register reg);

        void call(sysarch::p_sys_register reg);
        void call(CallStub* stub);

        template<class T>
        void call(T location) {
            add_opcode(new CallOpCode((void *)location));
        }

        void mov(sysarch::const_sys_register lhs,sysarch::DereferencedRegister rhs);
        void mov(sysarch::DereferencedRegister lhs,sysarch::const_sys_register rhs);
        void mov(sysarch::const_sys_register reg, int64 value);
        void mov(sysarch::const_sys_register destination,sysarch::const_sys_register source);

        void lea(sysarch::const_sys_register lhs, void* rhs);
        void syscall();
        void ret();

        void begin_frame();
        void end_frame();

        void emit_to(JitEmitter &writer);


    private:
        // Disable deletion
        JitCodeSegment(const JitCodeSegment&) = delete;
        JitCodeSegment(const JitCodeSegment&&) = delete;

        JitCodeSegment& operator=(JitCodeSegment&) = delete;
        JitCodeSegment& operator=(JitCodeSegment&&) = delete;
    };
}


#endif //__JitOpComposer_H_
