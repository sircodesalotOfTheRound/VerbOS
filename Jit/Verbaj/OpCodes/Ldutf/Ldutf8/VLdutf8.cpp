//
// Created by Reuben Kuhnert on 14/9/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VLdutf8.h"
#include "VerbajPrimitives.h"
#include "VirtualStackFrame.h"
#include "Instance.h"


void verbaj::VLdutf8::apply(jit::VirtualStackFrame& frame) const {
  auto& stage = frame.variable_stage();

  stage.new_local(variable_number_, VerbajPrimitives::vm_utf8, 1, false, true);

  types::Instance* instance = new(VerbajPrimitives::vm_utf8) types::Instance;
  types::Trait* head_trait = instance->head();

  head_trait->data<uint64_t>()[0] = string_.size();

  memcpy(&head_trait->data<char>(8)[0], &string_[0], string_.size());

  stage.with_register(variable_number_, [&](jit::VirtualVariableCheckout& checkout) {
    op::ProcessorOpCodeSet& opcodes = checkout.jit_opcodes();
    opcodes.lea(checkout.sys_register(), head_trait);
  });
}

