//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "Variable.h"
#include "CpuRegister.h"

#ifndef __VariableInfo_H_
#define __VariableInfo_H_

namespace jit {
  class VariableInfo {
    Variable* variable_;
    bool is_persisted_;
    const arch::CpuRegister* bound_register_;

  public:
    VariableInfo();

    bool contains_variable() const;
    Variable* variable() const;
    void set_variable(Variable* variable);
    void clear_variable();
    void clear_register_binding();
    bool is_register_bound() const;
    const arch::CpuRegister* bound_register() const;
    void set_persisted(bool is_persisted);
    bool is_persisted() const;
    void set_register_binding(const arch::CpuRegister* reg);
    int variable_number();
    const types::SystemType& type() const;
    int priority();


  private:
    void validate_register_bound() const;
    void validate_contains_variable() const;
  };
}


#endif //__VariableInfo_H_
