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

  // Temporary storage:
  std::vector<const arch::CpuRegister*> register_set_;

  // Pop registers until we find the one that matches sys_register.
  while (!available_registers_.empty()) {
    const arch::CpuRegister* current_register = pop_register_by_priority();

    // Once we find the register we're looking for, we can lock it then break.
    if (current_register == sys_register) {
      locked_registers_.insert(current_register);
      break;
    } else {
      register_set_.push_back(current_register);
    }
  }

  // Replay the remaining registers into the priority queue
  for (const arch::CpuRegister* current_register: register_set_) {
    available_registers_.push(current_register);
  }
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

  // If the variable is already staged:
  // Return if there was no request to bind to a specific register, or if we're
  // already bound to that register.
  // If something is already there, clear it out.
  if (is_staged(variable_number)) {
    if (to_register == nullptr || info.bound_register() == to_register) {
      return info;
    } else {
      if (is_staged(to_register)) {
        VariableInfo& variable_staged_in_register = at(to_register);
        variables_.persist(variable_staged_in_register.variable_number());
      }
    }
  }

  // If something is already staged in this register, save it.
  if (to_register != nullptr) {
    if (is_staged(to_register)) {
      VariableInfo& variable = at(to_register);
      variables_.persist(variable.variable_number());
    }
  }

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

  // Return the register to the stack.
  available_registers_.push(sys_register);
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

}

jit::VariableInfo& jit::RegisterPriorityQueue::at(int variable_number) {
  if (!is_staged(variable_number)) {
    throw std::logic_error("register is not staged");
  }

  return variables_.at(variable_number);
}

jit::VariableInfo& jit::RegisterPriorityQueue::at(const arch::CpuRegister* sys_register) {
  if (!is_staged(sys_register)) {
    throw std::logic_error("register is not staged");
  }

  int variable_number = register_to_var_map_.at(sys_register);
  return variables_.at(variable_number);
}

bool jit::RegisterPriorityQueue::is_staged(int variable_number) {
  return var_to_register_map_.find(variable_number) != var_to_register_map_.end();
}

bool jit::RegisterPriorityQueue::is_staged(const arch::CpuRegister* sys_register) {
  return register_to_var_map_.find(sys_register) != register_to_var_map_.end();
}
