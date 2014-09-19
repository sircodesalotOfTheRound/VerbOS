//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorLabelOpCode.h"

void op::ProcessorLabelOpCode::render(jit::JitRenderer&) const {
  /* NOP */
}

std::string op::ProcessorLabelOpCode::rep() const {
  std::stringstream representation;
  representation << "label: " << name_;

  return representation.str();
}

size_t op::ProcessorLabelOpCode::size() const {
  return 0;
}