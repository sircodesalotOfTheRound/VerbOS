//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorPushOpCode.h"

std::string op::ProcessorPushOpCode::rep() const {
  std::stringstream stream;
  stream << "push " << register_;
  return stream.str();
}

size_t op::ProcessorPushOpCode::size() const {
  return 1;
}

void op::ProcessorPushOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_opcode_masked(0x50, register_);
}