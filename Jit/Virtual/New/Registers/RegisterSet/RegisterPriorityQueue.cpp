//
// Created by Reuben Kuhnert on 14/9/30.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "RegisterPriorityQueue.h"

jit::RegisterPriorityQueue::RegisterPriorityQueue(VariableContainer& variables) : variables_(variables),
      available_registers_(RegisterSetOps(variables, register_to_var_map_)) {
      available_registers_.push(&arch::Intelx64Registers::rbx);
      available_registers_.push(&arch::Intelx64Registers::rcx);
      available_registers_.push(&arch::Intelx64Registers::rsi);
      available_registers_.push(&arch::Intelx64Registers::rdi);
      available_registers_.push(&arch::Intelx64Registers::r8);
      available_registers_.push(&arch::Intelx64Registers::r9);
      available_registers_.push(&arch::Intelx64Registers::r10);
      available_registers_.push(&arch::Intelx64Registers::r11);
      available_registers_.push(&arch::Intelx64Registers::r12);
      available_registers_.push(&arch::Intelx64Registers::r13);
      available_registers_.push(&arch::Intelx64Registers::r14);
      available_registers_.push(&arch::Intelx64Registers::r15);

      variables_.subscribe_on_insert([&](int variable_number) {
        release_binding(variable_number);
      });

      variables.subscribe_on_persist_requested([&](int variable_number) {
        release_binding(variable_number);
      });
    }

void jit::RegisterPriorityQueue::lock_register(const arch::CpuRegister* sys_register) {
  if (locked_registers_.find(sys_register) != locked_registers_.end()) {
    throw std::logic_error("register already locked");
  }

  locked_registers_.insert(sys_register);
}

void jit::RegisterPriorityQueue::unlock_register(const arch::CpuRegister* sys_register) {
  if (locked_registers_.find(sys_register) == locked_registers_.end()) {
    throw std::logic_error("register is not locked");
  }

  locked_registers_.erase(sys_register);
  available_registers_.push(sys_register);
}

jit::VariableInfo& jit::RegisterPriorityQueue::stage(int variable_number, const arch::CpuRegister* to_register) {
  VariableInfo& info = variables_.at(variable_number);

  // If no register is supplied, then request the most avaialable one.
  const arch::CpuRegister* sys_register;
  if (to_register == nullptr) {
    sys_register = pop_register_by_priority();
  } else {
    sys_register = to_register;
  }

  info.set_register_binding(sys_register);

  // Cache the relationship.
  register_to_var_map_.insert({sys_register, variable_number});
  var_to_register_map_.insert({variable_number, sys_register});

  return info;
}

void jit::RegisterPriorityQueue::release_binding(int variable_number) {
  if (var_to_register_map_.find(variable_number) != var_to_register_map_.end()) {
    const arch::CpuRegister* sys_register = var_to_register_map_.at(variable_number);

    var_to_register_map_.erase(variable_number);
    register_to_var_map_.erase(sys_register);

    if (locked_registers_.find(sys_register) != locked_registers_.end()) {
      unlock_register(sys_register);
    }
  }
}

const arch::CpuRegister* jit::RegisterPriorityQueue::pop_register_by_priority() {
  const arch::CpuRegister* top_register = available_registers_.top();
  available_registers_.pop();

  return top_register;
}

void jit::RegisterPriorityQueue::unlock_all_registers() {
  for (const arch::CpuRegister* sys_register : locked_registers_) {
    available_registers_.push(sys_register);
  }

  locked_registers_.clear();
}

void jit::RegisterPriorityQueue::re_prioritize() {
  std::vector<const arch::CpuRegister*> register_set_;

  while (!available_registers_.empty()) {
    register_set_.push_back(pop_register_by_priority());
  }

  for (const arch::CpuRegister* sys_register : register_set_) {
    available_registers_.push(sys_register);
  }
}