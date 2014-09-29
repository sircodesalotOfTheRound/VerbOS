//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "Variable.h"
#include "CpuRegister.h"

#ifndef __VariableInfo_H_
#define __VariableInfo_H_


class VariableInfo {
  Variable* variable_;
  arch::CpuRegister* bound_register_;

public:
  bool contains_variable() const { return variable_ != nullptr; }
  Variable* variable() const {
    validate_contains_variable();
    return variable_;
  }

  void set_variable(Variable* variable) { variable_ = variable;; }
  void clear_variable() { variable_ = nullptr; }

  bool is_register_bound() const { return bound_register_ != nullptr; }

  void set_register_binding(arch::CpuRegister* reg) {
    bound_register_ = reg;
  }

  arch::CpuRegister* bound_register() const {
    validate_register_bound();
    return bound_register_;
  }

private:
  void validate_register_bound() const {
    if (!is_register_bound()) {
      throw std::logic_error("is not bound to a register");
    }
  }

  void validate_contains_variable() const {
    if (!contains_variable()) {
      throw std::logic_error("does not contain a variable");
    }
  }
};


#endif //__VariableInfo_H_
