//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "JitRenderer.h"

void jit::JitRenderer::write_preamble64lhs(const arch::CpuRegister& reg) {
  if (reg.is_extended()) write_int8(0x49);
  else write_int8(0x48);
}

void jit::JitRenderer::write_preamble64rhs(const arch::CpuRegister& reg) {
  if (reg.is_extended()) write_int8(0x4c);
  else write_int8(0x48);
}

void jit::JitRenderer::write_preamble64(const arch::CpuRegister& lhs, const arch::CpuRegister& rhs) {
  // If both sides are extended, then the prefix is 0x4d.
  if (lhs.is_extended() && rhs.is_extended()) {
    write_int8(0x4d);

  } else if (lhs.is_extended() || rhs.is_extended()) {

    // Otherwise, lhs-extended is 0x49, and rhs is 0x4c.
    if (lhs.is_extended()) {
      write_int8(0x49);
    }
    else if (rhs.is_extended()) {
      write_int8(0x4c);
    }

  } else {
    // If neither side is extended:
    write_int8(0x48);

  }
}

void jit::JitRenderer::write_int8(uint8_t value) {
  memory_[write_offset_++] = value;
}

void jit::JitRenderer::write_int32(uint32_t value) {
  memory_[write_offset_++] = (byte) ((value) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 8) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 16) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 24) & 0xFF);
}

void jit::JitRenderer::write_int64(uint64_t value) {
  memory_[write_offset_++] = (byte) ((value) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 8) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 16) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 24) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 32) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 40) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 48) & 0xFF);
  memory_[write_offset_++] = (byte) ((value >> 56) & 0xFF);
}

void jit::JitRenderer::write_opcode(byte data) {
  memory_[write_offset_++] = data;
}

void jit::JitRenderer::write_opcode_masked(byte opcode, arch::ConstCpuRegisterRef sys_register) {
  write_opcode(opcode | sys_register.register_code());
}

void jit::JitRenderer::write_opcode_masked(byte opcode, arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs) {
  write_opcode(opcode | (lhs.register_code() << 3) | rhs.register_code());
}

void jit::JitRenderer::debug_print() {
  using namespace std;

  for (int index = 0; index < write_offset_; ++index) {
    if (index != 0 && index % 10 == 0) {
      cout << endl;
    }

    cout << setfill('0') << setw(2) << hex << (int) memory_[index] << " ";
  }
  cout << dec << endl;
}

void* jit::JitRenderer::memory() const {
  return memory_;
}

void* jit::JitRenderer::current_location() const {
  return &memory_[write_offset_];
}