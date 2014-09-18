//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorOpCodeSet.h"

void op::ProcessorOpCodeSet::debug_print() {
  for (auto& opcode : opcodes_) {
    std::cout << *opcode << std::endl;
  }
}
