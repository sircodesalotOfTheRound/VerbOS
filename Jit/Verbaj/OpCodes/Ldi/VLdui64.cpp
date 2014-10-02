//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VerbajPrimitives.h"
#include "Stackframe.h"
#include "VLdui64.h"
#include "FileInt64.h"
#include "FileInt8.h"

void verbaj::VLdui64::apply(jit::Stackframe& frame) const {
  using namespace jit;

  // Create a new virtual register and add it.
  auto& stage = frame.allocator();

  // Priority 1, non-member, non-classpointer.
  stage.insert(register_index, VerbajPrimitives::vm_uint64, 1, false, false);

  // Perform the load
  stage.with_variable(register_index, [&](jit::VariableCheckout& checkout) {
    perform_load(checkout);
  });
}

void verbaj::VLdui64::perform_load(jit::VariableCheckout& checkout) const {
  auto& sys_register = *checkout.sys_register();
  op::ProcessorOpCodeSet& opcodes = checkout.jit_opcodes();

  // Move the value to the register. Done.
  opcodes.mov(sys_register, value_);
}

verbaj::VerbajOpCodeBase* verbaj::VLdui64::load_op(std::istream& stream) {
  FileInt8 variable_number(stream);
  FileInt64 value(stream);

  return new VLdui64(variable_number, value);
}
