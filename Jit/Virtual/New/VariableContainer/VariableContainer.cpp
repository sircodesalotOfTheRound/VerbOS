//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VariableContainer.h"

jit::VariableContainer::VariableContainer(size_t size) {
  variables_.resize(size);
}

void jit::VariableContainer::validate_contains_variable(int variable_number) {
  if (!contains_variable(variable_number)) {
    throw std::logic_error("no variable at index");
  }
}

bool jit::VariableContainer::contains_variable(int variable_number) {
  return variables_.at((size_t)variable_number).contains_variable();
}

void jit::VariableContainer::subscribe_on_persist(std::function<void(int)> callback) {
  on_persist_.add(callback);
}

void jit::VariableContainer::subscribe_on_insert(std::function<void(int)> callback) {
  on_insert_.add(callback);
}

void jit::VariableContainer::subscribe_on_stage(std::function<void(int, bool, const arch::CpuRegister*)> callback) {
  on_stage_.add(callback);
}

void jit::VariableContainer::subscribe_on_stage_requested(std::function<void(int, bool, const arch::CpuRegister*)> callback) {
  on_stage_requested_.add(callback);
}

void jit::VariableContainer::subscribe_on_persist_requested(std::function<void(int)> callback) {
  on_persist_requested_.add(callback);
}

void jit::VariableContainer::subscribe_on_insert_requested(std::function<void(int)> callback) {
  on_insert_requested_.add(callback);
}

jit::VariableInfo& jit::VariableContainer::at(int variable_number) {
  validate_contains_variable(variable_number);
  return variables_.at((size_t)variable_number);
}

void jit::VariableContainer::stage(int variable_number, bool should_lock, const arch::CpuRegister* sys_register) {
  validate_contains_variable(variable_number);

  on_stage_requested_.update(variable_number, should_lock, sys_register);
  on_stage_.update(variable_number, should_lock, sys_register);
}

void jit::VariableContainer::persist(int variable_number) {
  validate_contains_variable(variable_number);

  on_persist_requested_.update(variable_number);
  on_persist_.update(variable_number);
}

void jit::VariableContainer::insert(int variable_number, const types::SystemType& type, int priority, bool is_member, bool is_object_reference) {
  Variable* variable = gc_.add(new Variable(variable_number, type, priority, is_member, is_object_reference));

  // Signal that we're about to perform the update. Then perform the update.
  on_insert_requested_.update(variable_number);
  variables_.at((size_t) variable_number).set_variable(variable);
  on_insert_.update(variable_number);
}

void jit::VariableContainer::persist_all() {
  for (VariableInfo& info : variables_) {
    if (info.contains_variable()) {
      persist(info.variable()->variable_number());
    }
  }
}

