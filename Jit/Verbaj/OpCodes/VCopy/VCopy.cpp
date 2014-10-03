//
// Created by Reuben Kuhnert on 14/10/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VCopy.h"
#include "Stackframe.h"
#include "Variable.h"

verbaj::VCopy::VCopy(int destination, int source) :
  destination_(destination),
  source_(source)
{

}

void verbaj::VCopy::apply(jit::Stackframe& frame) const {
  using namespace jit;

  auto& allocator = frame.allocator();
  if (!allocator.contains_variable(source_)) {
    throw std::logic_error("source does not contain variable");
  }

  auto& variable_info = allocator.at(source_);
  jit::Variable* variable = variable_info.variable();
  allocator.insert(destination_,
    variable->type(),
    variable->priority(),
    variable->is_member(),
    variable->is_object_reference());

  allocator.with_variables(destination_, source_, [&](VariableCheckout& destination, VariableCheckout& source) {
    auto& jit_opcodes = destination.jit_opcodes();

    jit_opcodes.mov(destination.sys_register(), source.sys_register());
  });

}

