//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __StackPersistStage_H_
#define __StackPersistStage_H_

#include "VariableContainer.h"
#include "ProcessorOpCodeSet.h"
#include "OsxRegisters.h"

class StackPersistStage {
  VariableContainer& container_;
  op::ProcessorOpCodeSet& jit_opcodes_;

public:
  StackPersistStage(VariableContainer& container, op::ProcessorOpCodeSet& jit_opcodes):
    container_(container),
    jit_opcodes_(jit_opcodes)
  {
    container_.subscribe_on_persist([&](int variable_number){
      persist_variable(variable_number);
    });
  }

private:
  void persist_variable(int variable_number) {
    static const auto& rbp = arch::OsxRegisters::rbp;
    VariableInfo& info = container_.at(variable_number);

    // If the variable is currently bound to a register.
    if (info.is_register_bound()) {
      auto* sys_register = info.bound_register();
      info.clear_register_binding();

      off_t offset = calculate_persistence_offset(info.variable());
      jit_opcodes_.mov(rbp[offset], *sys_register);
    }

    info.set_persisted(true);
  }

public:
  static off_t calculate_persistence_offset(const Variable* variable) {
    const static off_t stack_variable_size = sizeof(uint64_t);

    // Negative because the stack grows downward.
    // variable_number * variable_size + 8
    // +8 because the first address is reserved for the base pointer (rbp).
    // The rpb holds a pointer to the previous stack frame base.
    return -(stack_variable_size * variable->variable_number() + 8);
  }
};


#endif //__StackPersistStage_H_
