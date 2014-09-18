//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorSubRegToRegOpCode.h"

void op::ProcessorSubRegToRegOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_preamble64(lhs_, rhs_);

  renderer.write_opcode(0x29);
  renderer.write_opcode_masked(0xc0, rhs_, lhs_);
}
