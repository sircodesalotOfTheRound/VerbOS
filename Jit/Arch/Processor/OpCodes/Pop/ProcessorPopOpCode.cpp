//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorPopOpCode.h"

std::string op::ProcessorPopOpCode::rep() const {
  std::stringstream stream;
  stream << "pop " << register_;
  return stream.str();
}

size_t op::ProcessorPopOpCode::size() const {
  return 1;
}

void op::ProcessorPopOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_opcode_masked(0x58, register_);
}