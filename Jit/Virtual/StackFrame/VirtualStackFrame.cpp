//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VirtualStackFrame.h"

void jit::VirtualStackFrame::apply(jit::JitRenderer& renderer) {
  using namespace arch;

  // Clear the existing opcodes.
  jit_opcodes.clear();

  // Begin the frame
  jit_opcodes.push(Intelx64Registers::rbp);
  jit_opcodes.mov(Intelx64Registers::rbp, Intelx64Registers::rsp);
  jit_opcodes.sub(Intelx64Registers::rsp, 256);

  // Apply the Verbaj opcodes.
  for (auto& verbaj_op : verbaj_ops) {
    verbaj_op->apply(*this);
  }

  jit_opcodes.render(renderer);
}

void jit::VirtualStackFrame::debug_print() {
  // Clear the existing opcodes.
  jit_opcodes.debug_print();
}
