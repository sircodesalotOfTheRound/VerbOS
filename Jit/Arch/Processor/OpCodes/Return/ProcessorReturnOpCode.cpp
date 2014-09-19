//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorReturnOpCode.h"

void op::ProcessorReturnOpCode::render(jit::JitRenderer& renderer) const {
  renderer.write_opcode(0xc3);
}

size_t op::ProcessorReturnOpCode::size() const {
  return 1;
}

std::string op::ProcessorReturnOpCode::rep() const {
  return "ret";
}