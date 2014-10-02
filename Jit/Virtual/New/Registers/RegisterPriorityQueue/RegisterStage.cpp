//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "RegisterStage.h"

jit::RegisterStage::RegisterStage(VariableContainer& container, op::ProcessorOpCodeSet& jit_opcodes) : variables_(container),
    queue_(container),
    jit_opcodes_(jit_opcodes)
{
  variables_.subscribe_on_stage([&](int variable_number, const arch::CpuRegister* sys_register) {
    on_stage(variable_number, sys_register);
  });

  container.subscribe_on_insert([&](int variable_number) {
    unstage_variable(variable_number);
  });
}

void jit::RegisterStage::lock_register(const arch::CpuRegister* sys_register) {
  queue_.lock_register(sys_register);
}

void jit::RegisterStage::unlock_register(const arch::CpuRegister* sys_register) {
  queue_.unlock_register(sys_register);
}

void jit::RegisterStage::on_stage(int variable_number, const arch::CpuRegister* sys_register) {
  static const auto& rbp = arch::Intelx64Registers::rbp;

  // Capture which register
  bool is_persisted = false;
  const arch::CpuRegister* from_register = nullptr;
  const arch::CpuRegister* to_register = nullptr;

  // Capture the information about the variable before staging.
  if (variables_.contains_variable(variable_number)) {
    VariableInfo& variable = variables_.at(variable_number);
    if (variable.is_persisted()) {
     is_persisted = variable.is_persisted();
    }

    if (variable.is_register_bound()) {
      from_register = variable.bound_register();
    }
  }

  // Stage the variable.
  VariableInfo& info = queue_.stage(variable_number, sys_register);
  to_register = info.bound_register();

  // If the variable is currently persisted, we need to emit opcodes
  // to move the register from the stack to a physical-register.
  if (is_persisted) {
    info.set_persisted(false);

    off_t offset = StackPersistStage::calculate_persistence_offset(info.variable());
    jit_opcodes_.mov(*to_register, rbp[offset]);

  } else if (from_register != nullptr && (from_register != to_register)) {
    jit_opcodes_.mov(*to_register, *from_register);
  }
}

void jit::RegisterStage::unstage_variable(int variable_number) {
  if (queue_.is_staged(variable_number)) {
    variables_.at(variable_number).is_register_bound();
  }
}
