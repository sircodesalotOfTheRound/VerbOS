//
// Created by Reuben Kuhnert on 14-6-11.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "JitCodeSegment.h"
#include "JitStackFrameTemplate.h"
#include "JitEmitter.h"

void jit::JitEmitter::write_opcode(byte opcode) {
    write_int8(opcode);
}

void jit::JitEmitter::write_int8(int8 value) {
    _location[_offset++] = (uint8)value;
}

void jit::JitEmitter::write_int16(int16 value) {
    _location[_offset++] = (uint8)(value & 0xFF);
    _location[_offset++] = (uint8)((value >> 8) & 0xFF);
}

void jit::JitEmitter::write_int32(int32 value) {
    _location[_offset++] = (uint8)(value & 0xFF);
    _location[_offset++] = (uint8)((value >> 8) & 0xFF);
    _location[_offset++] = (uint8)((value >> 16) & 0xFF);
    _location[_offset++] = (uint8)((value >> 24) & 0xFF);
}

void jit::JitEmitter::write_int64(int64 value) {
    _location[_offset++] = (uint8)(value & 0xFF);
    _location[_offset++] = (uint8)((value >> 8) & 0xFF);
    _location[_offset++] = (uint8)((value >> 16) & 0xFF);
    _location[_offset++] = (uint8)((value >> 24) & 0xFF);
    _location[_offset++] = (uint8)((value >> 32) & 0xFF);
    _location[_offset++] = (uint8)((value >> 40) & 0xFF);
    _location[_offset++] = (uint8)((value >> 48) & 0xFF);
    _location[_offset++] = (uint8)((value >> 56) & 0xFF);
}

void jit::JitEmitter::write_register_masked(byte mask, sysarch::p_sys_register reg) {
    write_int8(mask | reg->register_code());
}

void jit::JitEmitter::write_opcode_masked(byte opcode, sysarch::p_sys_register reg) {
    write_int8(opcode | reg->register_code());
}

void jit::JitEmitter::write_prefix64() {
    write_int8(0x48);
}

void jit::JitEmitter::write_registers_masked(byte mask, sysarch::p_sys_register lhs, sysarch::p_sys_register rhs) {
    write_int8(mask | (lhs->register_code() << 3) | rhs->register_code());
}

void* jit::JitEmitter::emit(jit::JitStackFrameTemplate& segment) {
    void* address = (void *) this->current_address();
    segment.emit_to(*this);

    return address;
}

void *jit::JitEmitter::emit(jit::JitCodeSegment &segment) {
    void* address = (void*)this->current_address();
    segment.emit_to(*this);

    return address;
}

void jit::JitEmitter::emit(opcodes::OpCode &code) {
    code.render(*this);
}

void jit::JitEmitter::emit(opcodes::OpCode&& code) {
    code.render(*this);
}
