//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __VariableCheckout_H_
#define __VariableCheckout_H_

#include "Variable.h"
#include "CpuRegister.h"
#include "VariableInfo.h"
#include "ProcessorOpCodeSet.h"

class VariableCheckout {
  Variable* variable_;
  const arch::CpuRegister* sys_register_;
  op::ProcessorOpCodeSet& jit_opcodes_;

public:
  VariableCheckout(VariableInfo& info, op::ProcessorOpCodeSet& jit_opcodes) :
    variable_(info.variable()),
    sys_register_(info.bound_register()),
    jit_opcodes_(jit_opcodes)
  {

  }

  Variable* variable() { return variable_; }
  const arch::CpuRegister* sys_register() const { return sys_register_; }
  op::ProcessorOpCodeSet& jit_opcodes() { return jit_opcodes_; }
};


#endif //__VariableCheckout_H_
