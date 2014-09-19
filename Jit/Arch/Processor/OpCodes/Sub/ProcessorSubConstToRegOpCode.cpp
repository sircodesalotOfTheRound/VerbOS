//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorSubConstToRegOpCode.h"

void op::ProcessorSubConstToRegOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_preamble64lhs(lhs_);

  renderer.write_opcode(0x81);
  renderer.write_opcode_masked(0xec, lhs_);

  // Add only comes in 32 bit variant
  renderer.write_int32((uint32_t) rhs_);
}

std::string op::ProcessorSubConstToRegOpCode::rep() const {
  std::stringstream rep;
  rep << "sub " << lhs_ << ", " << rhs_;

  return rep.str();
}

size_t op::ProcessorSubConstToRegOpCode::size() const {
  return 5;
}