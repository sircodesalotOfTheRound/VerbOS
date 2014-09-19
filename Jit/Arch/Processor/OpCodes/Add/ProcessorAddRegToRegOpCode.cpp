//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorAddRegToRegOpCode.h"

void op::ProcessorAddRegToRegOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_preamble64(lhs_, rhs_);

  renderer.write_opcode(0x01);
  renderer.write_opcode_masked(0xc0, rhs_, lhs_);
}

std::string op::ProcessorAddRegToRegOpCode::rep() const {
  std::stringstream rep;
  rep << "add " << lhs_ << ", " << rhs_;

  return rep.str();
}

size_t op::ProcessorAddRegToRegOpCode::size() const {
  return 5;
}