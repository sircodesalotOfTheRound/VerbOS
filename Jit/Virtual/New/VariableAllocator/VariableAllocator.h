//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VariableAllocator_H_
#define __VariableAllocator_H_

#include "Variable.h"
#include "AutoCollector.h"
#include "VariableInfo.h"
#include "Event.h"
#include "VariableContainer.h"
#include "StackPersistStage.h"
#include "RegisterStage.h"

class VariableAllocator {
  VariableContainer variables_;
  RegisterStage register_stage_;
  StackPersistStage persist_stage_;

public:
  VariableAllocator(size_t size) :
    variables_(size),
    register_stage_(variables_),
    persist_stage_(variables_)
  {

  }

  void insert(int variable_number, const types::SystemType& type, int priority, bool is_member, bool is_object_reference) {
    variables_.insert(variable_number, type, priority, is_member, is_object_reference);
  }

  VariableInfo& at(int variable_number) {
    return variables_.at(variable_number);
  }

  bool contains_variable(int variable_number) {
    return variables_.contains_variable(variable_number);
  }

  void with_variable(int variable_number, std::function<void(Variable*)> callback) {
    variables_.stage(variable_number);
  }
};


#endif //__VariableAllocator_H_
