//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorAddConstToRegOpCode.h"

void op::ProcessorAddConstToRegOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_preamble64lhs(lhs_);

  renderer.write_opcode(0x81);
  renderer.write_opcode_masked(0xc0, lhs_);

  // Add only comes in 32 bit variant
  renderer.write_int32((uint32_t) rhs_);
}

std::string op::ProcessorAddConstToRegOpCode::rep() const {
  std::stringstream rep;
  rep << "add " << lhs_ << ", " << rhs_;

  return rep.str();
}

size_t op::ProcessorAddConstToRegOpCode::size() const {
  return 5;
}