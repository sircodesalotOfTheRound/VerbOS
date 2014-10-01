//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorOpCodeSet.h"
#include "ProcessorJumpOpCode.h"
#import "ProcessorCmpOpCode.h"

void op::ProcessorOpCodeSet::debug_print() {
  for (auto& opcode : opcodes_) {
    std::cout << *opcode << std::endl;
  }
}

void op::ProcessorOpCodeSet::render(jit::JitRenderer& renderer) {
  for (auto& opcode : opcodes_) {
    opcode->render(renderer);
  }
}

void op::ProcessorOpCodeSet::clear() {
  opcodes_.clear();
}

op::ProcessorOpCodeSet::iterator op::ProcessorOpCodeSet::begin() {
  return opcodes_.begin();
}

op::ProcessorOpCodeSet::iterator op::ProcessorOpCodeSet::end() {
  return opcodes_.end();
}

void op::ProcessorOpCodeSet::ret() {
  add(new ProcessorReturnOpCode());
}

void op::ProcessorOpCodeSet::label(std::string label) {
  add(new ProcessorLabelOpCode(label, *this));
}

void op::ProcessorOpCodeSet::add(arch::ConstCpuRegisterRef lhs, uint64_t rhs) {
  add(new op::ProcessorAddConstToRegOpCode(lhs, rhs));
}

void op::ProcessorOpCodeSet::add(arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs) {
  add(new op::ProcessorAddRegToRegOpCode(lhs, rhs));
}

void op::ProcessorOpCodeSet::sub(arch::ConstCpuRegisterRef lhs, uint64_t rhs) {
  add(new op::ProcessorSubConstToRegOpCode(lhs, rhs));
}

void op::ProcessorOpCodeSet::sub(arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs) {
  add(new op::ProcessorSubRegToRegOpCode(lhs, rhs));
}

void op::ProcessorOpCodeSet::mov(arch::ConstCpuRegisterRef sys_register, uint64_t value) {
  add(new op::ProcessorMovConstToRegOpCode(sys_register, value));
}

void op::ProcessorOpCodeSet::mov(arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs) {
  add(new op::ProcessorRegToRegMovOp(lhs, rhs));
}

void op::ProcessorOpCodeSet::mov(arch::ConstCpuRegisterRef lhs, arch::DereferencedCpuRegister rhs) {
  add(new op::ProcessorMovRegToMemOp(lhs, rhs, ProcessorMovRegToMemOp::DIRECTION::FROM_MEMORY));
}

void op::ProcessorOpCodeSet::mov(arch::DereferencedCpuRegister lhs, arch::ConstCpuRegisterRef rhs) {
  add(new op::ProcessorMovRegToMemOp(rhs, lhs, ProcessorMovRegToMemOp::DIRECTION::TO_MEMORY));
}

void op::ProcessorOpCodeSet::inc(arch::ConstCpuRegisterRef sys_register) {
  add(new op::ProcessorIncOpCode(sys_register));
}

void op::ProcessorOpCodeSet::dec(arch::ConstCpuRegisterRef sys_register) {
  add(new op::ProcessorDecOpCode(sys_register));
}

void op::ProcessorOpCodeSet::push(arch::ConstCpuRegisterRef sys_register) {
  add(new op::ProcessorPushOpCode(sys_register));
}

void op::ProcessorOpCodeSet::pop(arch::ConstCpuRegisterRef sys_register) {
  add(new op::ProcessorPopOpCode(sys_register));
}

void op::ProcessorOpCodeSet::jmp(std::string label) {
  add(new op::ProcessorJumpOpCode(label, *this));
}

void op::ProcessorOpCodeSet::lea(arch::ConstCpuRegisterRef sys_register, const void* object) {
  add(new op::ProcessorMovConstToRegOpCode(sys_register, (uintptr_t) object));
}

void op::ProcessorOpCodeSet::add_label(std::string name) {
  labels_.insert({ name, MemoryLabel(name) });
}

void op::ProcessorOpCodeSet::add_label(std::string name, void* location) {
  labels_.insert({ name, MemoryLabel(name, location) });
}

bool op::ProcessorOpCodeSet::contains_label(std::string name) const {
  return labels_.find(name) != labels_.end();
}

void op::ProcessorOpCodeSet::add_label_callback(std::string name, std::function<void(void*)> callback) {
  if (!contains_label(name)) {
    throw std::logic_error("no such label");
  }

  MemoryLabel& label = labels_.at(name);
  label.add_callback(callback);
}

void op::ProcessorOpCodeSet::set_label_address(std::string name, void* location) {
  if (!contains_label(name)) {
    throw std::logic_error("no such label");
  }

  MemoryLabel& label = labels_.at(name);
  label.set_location(location);
}

void* op::ProcessorOpCodeSet::get_label_address(std::string name) {
  MemoryLabel& label = labels_.at(name);

  if (!label.is_location_fixed()) {
    throw std::logic_error("label does not yet have a fixed memory location");
  }

  return label.memory_location();
}

bool op::ProcessorOpCodeSet::label_has_address(std::string name) {
  return get_label_address(name) != nullptr;
}

void op::ProcessorOpCodeSet::cmp(const arch::CpuRegister& lhs, const arch::CpuRegister& rhs) {
  add(new ProcessorCmpOpCode(lhs, rhs));
}
