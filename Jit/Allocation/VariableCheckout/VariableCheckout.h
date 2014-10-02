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

namespace jit {
class VariableCheckout {
  Variable* variable_;
  const arch::CpuRegister* sys_register_;
  op::ProcessorOpCodeSet& jit_opcodes_;

public:
  VariableCheckout(VariableInfo& info, op::ProcessorOpCodeSet& jit_opcodes);

  Variable* variable();
  const arch::CpuRegister* sys_register() const;
  op::ProcessorOpCodeSet& jit_opcodes();
};
}


#endif //__VariableCheckout_H_
