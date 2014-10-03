//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VariableInfo.h"

jit::VariableInfo::VariableInfo() : variable_(nullptr),
                                    is_persisted_(false),
                                    bound_register_(nullptr) {

}

bool jit::VariableInfo::contains_variable() const {
  return variable_ != nullptr;
}

jit::Variable* jit::VariableInfo::variable() const {
  validate_contains_variable();
  return variable_;
}

void jit::VariableInfo::set_variable(Variable* variable) {
  variable_ = variable;;
}

void jit::VariableInfo::clear_variable() {
  variable_ = nullptr;
}

void jit::VariableInfo::clear_register_binding() {
  bound_register_ = nullptr;
}

bool jit::VariableInfo::is_register_bound() const {
  return bound_register_ != nullptr;
}

const arch::CpuRegister* jit::VariableInfo::bound_register() const {
  validate_register_bound();
  return bound_register_;
}

void jit::VariableInfo::set_persisted(bool is_persisted) {
  is_persisted_ = is_persisted;
}

bool jit::VariableInfo::is_persisted() const {
  return is_persisted_;
}

void jit::VariableInfo::set_register_binding(const arch::CpuRegister* reg) {
  bound_register_ = reg;
}

int jit::VariableInfo::variable_number() {
  validate_contains_variable();
  return variable_->variable_number();
}

int jit::VariableInfo::priority() {
  validate_contains_variable();
  return variable_->priority();
}

void jit::VariableInfo::validate_register_bound() const {
  if (!is_register_bound()) {
    throw std::logic_error("is not bound to a register");
  }
}

void jit::VariableInfo::validate_contains_variable() const {
  if (!contains_variable()) {
    throw std::logic_error("does not contain a variable");
  }
}

types::SystemType const& jit::VariableInfo::type() const {
  validate_contains_variable();
  return variable_->type();
}
