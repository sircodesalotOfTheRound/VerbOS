//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "Stackframe.h"


jit::Stackframe::Stackframe(size_t max_objects, size_t max_constants):
  allocator_(max_objects, max_constants, jit_opcodes_)
{

}

jit::VariableAllocator& jit::Stackframe::allocator() {
  return allocator_;
}

op::ProcessorOpCodeSet& jit::Stackframe::jit_opcodes() {
  return jit_opcodes_;
}

void jit::Stackframe::apply(jit::JitRenderer& renderer) {
  using namespace arch;

  // Clear the existing opcodes.
  jit_opcodes_.clear();

  // Begin the frame
  jit_opcodes_.push(Intelx64Registers::rbp);
  jit_opcodes_.mov(Intelx64Registers::rbp, Intelx64Registers::rsp);
  jit_opcodes_.sub(Intelx64Registers::rsp, 256);

  // Apply the Verbaj opcodes.
  for (auto& verbaj_op : verbaj_ops) {
    verbaj_op->apply(*this);
  }

  jit_opcodes_.render(renderer);
}

void jit::Stackframe::debug_print() {
  // Clear the existing opcodes.
  jit_opcodes_.debug_print();
}