//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorIncOpCode.h"

size_t op::ProcessorIncOpCode::size() const {
  return 3;
}

std::string op::ProcessorIncOpCode::rep() const {
  return "inc";
}

void op::ProcessorIncOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_preamble64lhs(sys_register_);
  renderer.write_opcode(0xFF);
  renderer.write_opcode_masked(0xc0, sys_register_);
}