//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __JitRenderer_H_
#define __JitRenderer_H_

#include "TypeDef.h"
#include "CpuRegister.h"

namespace jit {
    class JitRenderer {
        byte* memory_;
        off_t write_offset_;

    public:
        JitRenderer(void* memory) : memory_((byte*)memory), write_offset_(0) { }

        void write_preamble64() {
            write_int8(0x48);
        }

        void write_int8(uint8_t value) {
            memory_[write_offset_++] = value;
        }

        void write_int32(uint32_t value) {
            memory_[write_offset_++] = (byte)((value) & 0xFF);
            memory_[write_offset_++] = (byte)((value >> 8) & 0xFF);
            memory_[write_offset_++] = (byte)((value >> 16) & 0xFF);
            memory_[write_offset_++] = (byte)((value >> 24) & 0xFF);
        }

        void write_opcode(byte data) {
            memory_[write_offset_++] = data;
        }

        void write_opcode_masked(byte opcode, const processor::CpuRegister& sys_register) {
            write_opcode(opcode | sys_register.register_code());
        }

        void* memory() const { return memory_;}
        void* current_location() const { return &memory_[write_offset_]; }
    };
}


#endif //__JitRenderer_H_
