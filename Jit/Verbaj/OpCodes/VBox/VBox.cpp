//
// Created by Reuben Kuhnert on 14/9/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VBox.h"
#include "VirtualStackFrame.h"
#include "VerbajPrimitives.h"
#include "FileInt8.h"

void verbaj::VBox::apply(jit::VirtualStackFrame& frame) const {
  auto& stage = frame.variable_stage();

  if (!stage.contains_variable(variable_number_)) {
    throw std::logic_error("stage does not contain a variable at this index.");
  }

  stage.stage_argument(variable_number_);
  stage.persist_variables();
  frame.sys_ops().call((void*)&instantiate);

  // TODO: Make the move directly to memory (easier said than done because of the variable type change).
  stage.with_register(variable_number_, [&](jit::VirtualVariableCheckout& checkout) {
    op::ProcessorOpCodeSet& opcodes = checkout.jit_opcodes();
    opcodes.mov(checkout.sys_register(), arch::Intelx64Registers::rax);
  });

  stage.new_local(variable_number_, VerbajPrimitives::vm_box_of_uint64, 1, false, true);
}

types::Trait* verbaj::VBox::instantiate(uint64_t value) {
  types::Instance* instance = new(VerbajPrimitives::vm_box_of_uint64) types::Instance;
  instance->head()->data<uint64_t>()[0] = value;

  // Return the address of the boxed value.
  return instance->head();
}

verbaj::VerbajOpCodeBase* verbaj::VBox::load_op(std::istream& stream) {
  FileInt8 source(stream);
  FileInt8 destination(stream);

  return new VBox(source);
}
