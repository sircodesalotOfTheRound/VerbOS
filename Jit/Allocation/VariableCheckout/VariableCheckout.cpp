
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VariableCheckout.h"

jit::VariableCheckout::VariableCheckout(VariableInfo& info, op::ProcessorOpCodeSet& jit_opcodes)
  : variable_(info.variable()),
   sys_register_(info.bound_register()),
   jit_opcodes_(jit_opcodes)
{

}
op::ProcessorOpCodeSet& jit::VariableCheckout::jit_opcodes() { return jit_opcodes_; }
const arch::CpuRegister& jit::VariableCheckout::sys_register() const { return *sys_register_; }
jit::Variable* jit::VariableCheckout::variable() { return variable_; }

