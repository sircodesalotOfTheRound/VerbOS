//
// Created by Reuben Kuhnert on 14-6-11.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#ifndef __JitMemWriter_H_
#define __JitMemWriter_H_

#include "Types.h"
#include "SystemRegister.h"
#include "OpCode.h"

namespace opcodes {
    class OpCode;
}

namespace jit {
    class JitStackFrameTemplate;
    class JitCodeSegment;

    class JitEmitter {
        byte* _location;
        size_t _offset;

    public:
        JitEmitter(byte* location)
            : _location(location), _offset(0)
        {

        }

        void write_opcode(byte opcode);
        void write_opcode_masked(byte opcode, sysarch::p_sys_register reg);

        void write_register_masked(byte opcode, sysarch::p_sys_register reg);
        void write_registers_masked(byte mask, sysarch::p_sys_register reg, sysarch::p_sys_register rhs);

        void write_int8(int8 value);
        void write_int16(int16 value);
        void write_int32(int32 value);
        void write_int64(int64 value);

        void write_prefix64();

        size_t offset() { return _offset; }

        uintptr_t current_address() { return (uintptr_t) _location + _offset; }

        void emit(opcodes::OpCode& opcode);
        void emit(opcodes::OpCode&& opcode);

        void* emit(JitCodeSegment& segment);
        void* emit(JitStackFrameTemplate& segment);
    };
}

#endif //__JitMemWriter_H_
