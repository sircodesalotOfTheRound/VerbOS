//
// Created by Reuben Kuhnert on 14/10/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorCmpOpCode.h"

op::ProcessorCmpOpCode::ProcessorCmpOpCode(const arch::CpuRegister& lhs, const arch::CpuRegister& rhs):
  lhs_(lhs),
  rhs_(rhs)
{

}

std::string op::ProcessorCmpOpCode::rep() const {
  std::stringstream stream;
  stream << "cmp " << lhs_ << ", " << rhs_;

  return stream.str();
}

size_t op::ProcessorCmpOpCode::size() const {
  return 0;
}

void op::ProcessorCmpOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_preamble64(lhs_, rhs_);
  renderer.write_opcode(0x39);
  renderer.write_opcode_masked(0xc0, rhs_, lhs_);
}
