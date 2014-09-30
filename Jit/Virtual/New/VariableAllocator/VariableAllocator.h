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
#import "VariableCheckout.h"

class VariableAllocator {
  size_t max_objects_;
  size_t max_constants_;
  VariableContainer variables_;
  RegisterStage register_stage_;
  StackPersistStage persist_stage_;
  op::ProcessorOpCodeSet& jit_opcodes_;

public:
  VariableAllocator(size_t max_objects, size_t max_constants, op::ProcessorOpCodeSet& jit_opcodes) :
    max_objects_(max_objects),
    max_constants_(max_constants),
    variables_(max_objects + max_constants),
    register_stage_(variables_, jit_opcodes),
    persist_stage_(variables_, jit_opcodes),
    jit_opcodes_(jit_opcodes)
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

  void persist_variables() {
    variables_.persist_all();
  }

  size_t max_objects() const { return max_objects_; }
  size_t max_constants() const { return max_constants_; }

  void with_variable(int variable_number, std::function<void(VariableCheckout&)> callback) {
    variables_.stage(variable_number, true, nullptr);

    VariableInfo& info = variables_.at(variable_number);
    VariableCheckout checkout (info, jit_opcodes_);
    callback(checkout);

    register_stage_.unlock_register(info.bound_register());
  }
};


#endif //__VariableAllocator_H_
