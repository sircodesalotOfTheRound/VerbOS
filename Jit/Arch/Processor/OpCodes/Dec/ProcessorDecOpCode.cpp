//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorDecOpCode.h"

size_t op::ProcessorDecOpCode::size() const {
  return 3;
}

std::string op::ProcessorDecOpCode::rep() const {
  return "inc";
}

void op::ProcessorDecOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_preamble64lhs(sys_register_);
  renderer.write_opcode(0xFF);
  renderer.write_opcode_masked(0xc8, sys_register_);
}