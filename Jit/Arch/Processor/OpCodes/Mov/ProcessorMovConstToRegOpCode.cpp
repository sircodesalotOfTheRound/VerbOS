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
