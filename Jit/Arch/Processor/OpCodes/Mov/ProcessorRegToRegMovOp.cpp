//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorRegToRegMovOp.h"

void op::ProcessorRegToRegMovOp::render(jit::JitRenderer& renderer) const {
  renderer.write_preamble64(lhs_, rhs_);

  renderer.write_opcode(0x89);

  // Note op-code is backwards
  renderer.write_opcode_masked(0xc0, rhs_, lhs_);
}

std::string op::ProcessorRegToRegMovOp::rep() const {
  std::stringstream stream;
  stream << "mov " << lhs_ << ", " << rhs_;

  return stream.str();
}

size_t op::ProcessorRegToRegMovOp::size() const {
  return 5;
}