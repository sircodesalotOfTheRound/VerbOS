//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VariableAllocator_H_
#define __VariableAllocator_H_

#include "Variable.h"
#include "Collector.h"
#import "VariableInfo.h"
#include "Event.h"

class VariableAllocator {
  helpers::Collector<Variable> collector_;
  helpers::Event<void(Variable*)> on_insertion_;
  std::vector<VariableInfo> variables_;

public:
  VariableAllocator(size_t size) {
    variables_.resize(size);
  }

  void insert(int variable_number, const types::SystemType& type, int priority, bool is_member, bool is_object_reference) {
    Variable* variable = collector_.add(new Variable(variable_number, type, priority, is_member, is_object_reference));
    variables_.at((size_t) variable_number).set_variable(variable);

    on_insertion_.update(variable);
  }

  Variable* at(int variable_number) {
    validate_contains_variable(variable_number);
    return variables_.at((size_t)variable_number).variable();
  }

  void subscribe_on_variable_inserted(std::function<void(Variable*)> callback) {
    on_insertion_.add(callback);
  }

  bool contains_variable(int variable_number) {
    return variables_.at((size_t)variable_number).contains_variable();
  }

private:
  void validate_contains_variable(int variable_number) {
    if (!contains_variable(variable_number)) {
      throw std::logic_error("no variable at index");
    }
  }
};


#endif //__VariableAllocator_H_
