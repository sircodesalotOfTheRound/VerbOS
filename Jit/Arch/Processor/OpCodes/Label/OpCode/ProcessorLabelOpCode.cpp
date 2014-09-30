//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorLabelOpCode.h"
#include "ProcessorOpCodeSet.h"

op::ProcessorLabelOpCode::ProcessorLabelOpCode(std::string name, op::ProcessorOpCodeSet& jit_opcodes):
  name_(name),
  jit_opcodes_(jit_opcodes)
{

}

void op::ProcessorLabelOpCode::render(jit::JitRenderer& renderer) const {
  // Basically the job of a label is to mark a particlar address.
  // Create the label if it hasn't already been created by say 'jmp'.
  // Otherwise fill in the address (this will force the associated callbacks
  // that have been waiting for this label's address to fire).
  if (!jit_opcodes_.contains_label(name_)) {
    jit_opcodes_.add_label(name_, renderer.current_location());
  } else {
    jit_opcodes_.set_label_address(name_, renderer.current_location());
  }
}

std::string op::ProcessorLabelOpCode::rep() const {
  std::stringstream representation;
  representation << "label: " << name_;

  return representation.str();
}

size_t op::ProcessorLabelOpCode::size() const {
  return 0;
}

