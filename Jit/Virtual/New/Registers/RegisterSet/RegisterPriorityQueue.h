//
// Created by Reuben Kuhnert on 14/9/30.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __RegisterPriorityQueue_
#define __RegisterPriorityQueue_

#include <unordered_set>
#include <set>
#include <queue>
#include "VariableContainer.h"
#include "OsxRegisters.h"

class RegisterPriorityQueue {
  VariableContainer& variables_;

  class RegisterSetOps {
    VariableContainer& variables_;
    std::unordered_map<const arch::CpuRegister*, int>& register_to_var_map_;

  public:
    RegisterSetOps(VariableContainer& variables, std::unordered_map<const arch::CpuRegister*, int>& register_to_var_map)
      :
      variables_(variables),
      register_to_var_map_(register_to_var_map) {

    }

    bool operator()(const arch::CpuRegister* lhs, const arch::CpuRegister* rhs) {
      int lhs_priority = get_priority_by_register(lhs);
      int rhs_priority = get_priority_by_register(rhs);

      return lhs_priority > rhs_priority;
    }

  private:
    int get_priority_by_register(const arch::CpuRegister* sys_register) {
      if (register_to_var_map_.find(sys_register) == register_to_var_map_.end()) {
        return 0;
      }

      int variable_number = register_to_var_map_.find(sys_register)->second;
      return variables_.at(variable_number).priority();
    }
  };

  std::priority_queue<const arch::CpuRegister*, std::vector<const arch::CpuRegister*>, RegisterSetOps> available_registers_;
  std::unordered_set<const arch::CpuRegister*> locked_registers_;
  std::unordered_map<int, const arch::CpuRegister*> var_to_register_map_;
  std::unordered_map<const arch::CpuRegister*, int> register_to_var_map_;

public:
  RegisterPriorityQueue(VariableContainer& variables) :
    variables_(variables),
    available_registers_(RegisterSetOps(variables, register_to_var_map_)) {
    available_registers_.push(&arch::OsxRegisters::rbx);
    available_registers_.push(&arch::OsxRegisters::rcx);
    available_registers_.push(&arch::OsxRegisters::rsi);
    available_registers_.push(&arch::OsxRegisters::rdi);
    available_registers_.push(&arch::OsxRegisters::r8);
    available_registers_.push(&arch::OsxRegisters::r9);
    available_registers_.push(&arch::OsxRegisters::r10);
    available_registers_.push(&arch::OsxRegisters::r11);
    available_registers_.push(&arch::OsxRegisters::r12);
    available_registers_.push(&arch::OsxRegisters::r13);
    available_registers_.push(&arch::OsxRegisters::r14);
    available_registers_.push(&arch::OsxRegisters::r15);

    variables_.subscribe_on_insert([&](int variable_number) {
      on_insert(variable_number);
    });
  }

  void unlock_register(const arch::CpuRegister* sys_register) {
    if (locked_registers_.find(sys_register) == locked_registers_.end()) {
      throw std::logic_error("register is not locked");
    }

    locked_registers_.erase(sys_register);
    available_registers_.push(sys_register);
  }

public:
  VariableInfo& stage(int variable_number, bool should_lock, const arch::CpuRegister* to_register) {
    VariableInfo& info = variables_.at(variable_number);

    // If no register is supplied, then request the most avaialable one.
    const arch::CpuRegister* sys_register;
    if (to_register == nullptr) {
      sys_register = pop_register_by_priority();
    } else {
      sys_register = to_register;
    }


    info.set_register_binding(sys_register);

    // Cache the relationship.
    register_to_var_map_.insert({sys_register, variable_number});
    var_to_register_map_.insert({variable_number, sys_register});

    // If we want to lock the register so it can't be reused, then do so.
    // Else, re-add it to the priority queue.
    if (should_lock) {
      locked_registers_.insert(sys_register);
    } else {
      available_registers_.push(sys_register);
    }

    return info;
  }

private:
  // If a new variable is inserted over an existing bound-to-register value,
  // then remove the binding, since it's no longer valid.
  void on_insert(int variable_number) {
    if (var_to_register_map_.find(variable_number) != var_to_register_map_.end()) {
      std::cout << "removing variable @" << variable_number << std::endl;
      const arch::CpuRegister* sys_register = var_to_register_map_.at(variable_number);

      var_to_register_map_.erase(variable_number);
      register_to_var_map_.erase(sys_register);

      if (locked_registers_.find(sys_register) != locked_registers_.end()) {
        unlock_register(sys_register);
      }
    }
  }

  const arch::CpuRegister* pop_register_by_priority() {
    const arch::CpuRegister* top_register = available_registers_.top();
    available_registers_.pop();

    return top_register;
  }


  void unlock_registers() {

  }


  // Reprioritize the priority queue.
  void re_prioritize() {
    std::vector<const arch::CpuRegister*> register_set_;

    while (!available_registers_.empty()) {
      register_set_.push_back(pop_register_by_priority());
    }

    for (const arch::CpuRegister* sys_register : register_set_) {
      available_registers_.push(sys_register);
    }
  }

};


#endif //__RegisterSet_H_
