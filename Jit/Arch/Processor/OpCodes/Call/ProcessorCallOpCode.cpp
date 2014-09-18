//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorCallOpCode.h"

void op::ProcessorCallOpCode::render(jit::JitRenderer& renderer) const {
  using namespace std;
  static off_t opcode_size = 5;

  uintptr_t current_memory_location = (uintptr_t) renderer.current_location();

  renderer.write_opcode(0xe8);
  renderer.write_int32((uint32_t) (location_ - (current_memory_location + opcode_size)));
}
