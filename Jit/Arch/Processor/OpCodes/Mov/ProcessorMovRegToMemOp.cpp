//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorMovRegToMemOp.h"

void op::ProcessorMovRegToMemOp::render(jit::JitRenderer& renderer) const {
  if (direction_ == DIRECTION::FROM_MEMORY) {
    renderer.write_preamble64(memory_location_.sys_register(), register_);
    renderer.write_opcode(0x8b);

  } else {
    renderer.write_preamble64(memory_location_.sys_register(), register_);
    renderer.write_opcode(0x89);
  }

  // For short offsets
  // TODO: implement long offsets
  if (memory_location_.offset() == 0) {
    renderer.write_opcode_masked(0x00, register_, memory_location_.sys_register());
  } else {
    renderer.write_opcode_masked(0x40, register_, memory_location_.sys_register());
    renderer.write_int8((uint8_t) memory_location_.offset());
  }
}

size_t op::ProcessorMovRegToMemOp::size() const {
  return 3;
}

std::string op::ProcessorMovRegToMemOp::rep() const {
  std::stringstream stream;

  if (direction_ == DIRECTION::TO_MEMORY) {
    stream << "mov " << memory_location_ << ", " << register_;
  } else {
    stream << "mov " << register_ << ", " << memory_location_;
  }

  return stream.str();
}