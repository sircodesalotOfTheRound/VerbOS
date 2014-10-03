//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorMovConstToRegOpCode.h"

void op::ProcessorMovConstToRegOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_preamble64lhs(lhs_);

  renderer.write_opcode_masked(0xb8, lhs_);
  renderer.write_int64(rhs_);

}

size_t op::ProcessorMovConstToRegOpCode::size() const {
  return 5;
}

std::string op::ProcessorMovConstToRegOpCode::rep() const {
  std::stringstream stream;
  stream << "mov " << lhs_ << ", 0x" << std::hex << rhs_ << std::dec;

  return stream.str();
}