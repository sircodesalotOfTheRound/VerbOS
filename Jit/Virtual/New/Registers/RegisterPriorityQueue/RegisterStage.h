//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __RegisterStage_H_
#define __RegisterStage_H_

#include "VariableContainer.h"
#include "OsxRegisters.h"
#include "ProcessorOpCodeSet.h"
#include "StackPersistStage.h"
#include "RegisterPriorityQueue.h"


class RegisterStage {
  VariableContainer& variables_;
  RegisterPriorityQueue queue_;
  op::ProcessorOpCodeSet& jit_opcodes_;

public:
  RegisterStage(VariableContainer& container, op::ProcessorOpCodeSet& jit_opcodes) :
    variables_(container),
    queue_(container),
    jit_opcodes_(jit_opcodes)
  {
    variables_.subscribe_on_stage([&](int variable_number, bool should_lock, const arch::CpuRegister* sys_register) {
      on_request_stage(variable_number, should_lock, sys_register);
    });

    container.subscribe_on_insert([&](int variable_number) {
      unstage_variable(variable_number);
    });
  }

public:
  bool is_staged(int variable_number) {
    if (variables_.at(variable_number).contains_variable()) {
      return variables_.at(variable_number).is_register_bound();
    }

    return false;
  }

  void unlock_register(const arch::CpuRegister* sys_register) {
    queue_.unlock_register(sys_register);
  }

private:
  void on_request_stage(int variable_number, bool should_lock, const arch::CpuRegister* sys_register) {
    static const auto& rbp = arch::OsxRegisters::rbp;

    if (!is_staged(variable_number)) {
      // Stage the variable.
      VariableInfo& info = queue_.stage(variable_number, should_lock, sys_register);

      // If the variable is currently persisted, we need to emit opcodes
      // to move the register from the stack to a physical-register.
      if (info.is_persisted()) {
        info.set_persisted(false);

        off_t offset = StackPersistStage::calculate_persistence_offset(info.variable());
        jit_opcodes_.mov(*info.bound_register(), rbp[offset]);
      }
    }
  }

  void unstage_variable(int variable_number) {
    if (is_staged(variable_number)) {
      variables_.at(variable_number).is_register_bound();
    }
  }
};


#endif //__RegisterStage_H_
