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
#include "ArgumentStagingFactory.h"

namespace jit {
class VariableAllocator {
  size_t max_objects_;
  size_t max_constants_;
  VariableContainer variables_;
  RegisterStage register_stage_;
  StackPersistStage persist_stage_;
  op::ProcessorOpCodeSet& jit_opcodes_;
  ArgumentStagingFactory argument_staging_factory_;

public:
  VariableAllocator(size_t max_objects, size_t max_constants, op::ProcessorOpCodeSet& jit_opcodes);

  void insert(int variable_number, const types::SystemType& type, int priority, bool is_member, bool is_object_reference);
  VariableInfo& at(int variable_number);
  bool contains_variable(int variable_number);
  void persist_variables();
  size_t max_objects() const;
  size_t max_constants() const;
  void with_variable(int variable_number, std::function<void(VariableCheckout&)> callback);
  void with_variables(int left_var, int right_var, std::function<void(VariableCheckout&, VariableCheckout&)> callback);
  void stage_argument(int variable_number);
  void unstage_arguments();
};
}



#endif //__VariableAllocator_H_
