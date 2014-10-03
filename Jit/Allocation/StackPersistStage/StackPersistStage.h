//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __StackPersistStage_H_
#define __StackPersistStage_H_

#include "VariableContainer.h"
#include "ProcessorOpCodeSet.h"
#include "Intelx64Registers.h"

namespace jit {
  class StackPersistStage {
    VariableContainer& variables_;
    op::ProcessorOpCodeSet& jit_opcodes_;

  public:
    StackPersistStage(VariableContainer& container, op::ProcessorOpCodeSet& jit_opcodes);

  private:
    void on_insert(int variable_number);
    void persist_variable(int variable_number);

  public:
    static off_t calculate_persistence_offset(const Variable* variable);
  };
}


#endif //__StackPersistStage_H_
