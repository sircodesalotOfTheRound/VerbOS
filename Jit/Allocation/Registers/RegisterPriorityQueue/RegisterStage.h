//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __RegisterStage_H_
#define __RegisterStage_H_

#include "VariableContainer.h"
#include "Intelx64Registers.h"
#include "ProcessorOpCodeSet.h"
#include "StackPersistStage.h"
#include "RegisterPriorityQueue.h"

namespace jit {
  class RegisterStage {
    VariableContainer& variables_;
    RegisterPriorityQueue queue_;
    op::ProcessorOpCodeSet& jit_opcodes_;

  public:
    RegisterStage(VariableContainer& container, op::ProcessorOpCodeSet& jit_opcodes);

  public:
    void lock_register(const arch::CpuRegister* sys_register);
    void unlock_register(const arch::CpuRegister* sys_register);

  private:
    void on_stage(int variable_number, const arch::CpuRegister* sys_register);
    void unstage_variable(int variable_number);
  };
}


#endif //__RegisterStage_H_
