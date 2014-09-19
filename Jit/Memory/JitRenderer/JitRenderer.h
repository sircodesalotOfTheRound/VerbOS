//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __JitRenderer_H_
#define __JitRenderer_H_

#import <iomanip>
#include "TypeDef.h"
#include "CpuRegister.h"

namespace jit {
  class JitRenderer {
    byte* memory_;
    off_t write_offset_;

  public:
    JitRenderer(void* memory) : memory_((byte*) memory), write_offset_(0) {
    }

    void write_preamble64lhs(const arch::CpuRegister& reg);
    void write_preamble64rhs(const arch::CpuRegister& reg);
    void write_preamble64(const arch::CpuRegister& lhs, const arch::CpuRegister& rhs);
    void write_int8(uint8_t value);
    void write_int32(uint32_t value);
    void write_int64(uint64_t value);
    void write_opcode(byte data);
    void write_opcode_masked(byte opcode, arch::ConstCpuRegisterRef sys_register);
    void write_opcode_masked(byte opcode, arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs);
    void debug_print();
    void* memory() const;
    void* current_location() const;
  };
}


#endif //__JitRenderer_H_
