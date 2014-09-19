//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VerbajOpCodeSet.h"

void verbaj::VerbajOpCodeSet::add(VerbajOpCodeBase* op) {
  std::unique_ptr<VerbajOpCodeBase> opcode(op);
  opcodes_.push_back(std::move(opcode));
}

verbaj::VerbajOpCodeSet::iterator verbaj::VerbajOpCodeSet::begin() {
  return opcodes_.begin();
}


verbaj::VerbajOpCodeSet::iterator verbaj::VerbajOpCodeSet::end() {
  return opcodes_.end();
}
