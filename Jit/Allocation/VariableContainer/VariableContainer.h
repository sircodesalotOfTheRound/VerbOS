//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VariableContainer_H_
#define __VariableContainer_H_

#include "Variable.h"
#include "AutoCollector.h"
#include "Event.h"
#include "VariableInfo.h"

namespace jit {
class VariableContainer {
  helpers::AutoCollector<Variable> gc_;

  helpers::Event<void(int)> on_insert_requested_;
  helpers::Event<void(int)> on_insert_;

  helpers::Event<void(int)> on_persist_requested_;
  helpers::Event<void(int)> on_persist_;

  helpers::Event<void(int, const arch::CpuRegister*)> on_stage_requested_;
  helpers::Event<void(int, const arch::CpuRegister*)> on_stage_;

  std::vector<VariableInfo> variables_;

public:
  VariableContainer(size_t size);

  void insert(int variable_number, const types::SystemType& type, int priority, bool is_member, bool is_object_reference);
  void persist_all();
  void persist(int variable_number);
  void stage(int variable_number, const arch::CpuRegister* sys_register);
  VariableInfo& at(int variable_number);
  void subscribe_on_insert_requested(std::function<void(int)> callback);
  void subscribe_on_persist_requested(std::function<void(int)> callback);
  void subscribe_on_stage_requested(std::function<void(int, const arch::CpuRegister*)> callback);
  void subscribe_on_stage(std::function<void(int, const arch::CpuRegister*)> callback);
  void subscribe_on_insert(std::function<void(int)> callback);
  void subscribe_on_persist(std::function<void(int)> callback);
  bool contains_variable(int variable_number);

private:
  void validate_contains_variable(int variable_number);

};
}


#endif //__VariableContainer_H_
