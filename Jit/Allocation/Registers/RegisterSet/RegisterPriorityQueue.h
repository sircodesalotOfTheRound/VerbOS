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
#include "Intelx64Registers.h"

namespace jit {
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
    RegisterPriorityQueue(VariableContainer& variables);
    void lock_register(const arch::CpuRegister* sys_register);
    void unlock_register(const arch::CpuRegister* sys_register);

    VariableInfo& at(int variable_number);
    VariableInfo& at(const arch::CpuRegister* sys_register);

    bool is_staged(int variable_number);
    bool is_staged(const arch::CpuRegister* sys_register);


  public:
    VariableInfo& stage(int variable_number, const arch::CpuRegister* to_register);

  private:
    void release_binding(int variable_number);
    const arch::CpuRegister* pop_register_by_priority();
    void unlock_all_registers();
    void re_prioritize();
  };
}


#endif //__RegisterSet_H_
