//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VariableAllocator.h"

jit::VariableAllocator::VariableAllocator(size_t max_objects, size_t max_constants, op::ProcessorOpCodeSet& jit_opcodes)
  : max_objects_(max_objects),
    max_constants_(max_constants),
    variables_(max_objects + max_constants),
    register_stage_(variables_, jit_opcodes),
    persist_stage_(variables_, jit_opcodes),
    jit_opcodes_(jit_opcodes) {

  }

void jit::VariableAllocator::insert(int variable_number, const types::SystemType& type, int priority, bool is_member, bool is_object_reference) {
  variables_.insert(variable_number, type, priority, is_member, is_object_reference);
}

jit::VariableInfo& jit::VariableAllocator::at(int variable_number) {
  return variables_.at(variable_number);
}

bool jit::VariableAllocator::contains_variable(int variable_number) {
  return variables_.contains_variable(variable_number);
}

void jit::VariableAllocator::persist_variables() {
  variables_.persist_all();
}

size_t jit::VariableAllocator::max_objects() const { return max_objects_; }

size_t jit::VariableAllocator::max_constants() const { return max_constants_; }

void jit::VariableAllocator::with_variable(int variable_number, std::function<void(VariableCheckout&)> callback) {
  variables_.stage(variable_number, nullptr);

  VariableInfo& info = variables_.at(variable_number);
  VariableCheckout checkout (info, jit_opcodes_);

  register_stage_.lock_register(info.bound_register());
  callback(checkout);
  register_stage_.unlock_register(info.bound_register());
}

void jit::VariableAllocator::stage_argument(int variable_number) {
  auto cpu_register = argument_staging_factory_.determine_register();

  variables_.stage(variable_number, cpu_register);
  register_stage_.lock_register(cpu_register);
}
