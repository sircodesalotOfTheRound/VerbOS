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

class VariableContainer {
  helpers::AutoCollector<Variable> gc_;

  helpers::Event<void(int)> on_insert_requested_;
  helpers::Event<void(int)> on_insert_;

  helpers::Event<void(int)> on_persist_requested_;
  helpers::Event<void(int)> on_persist_;

  helpers::Event<void(int)> on_stage_requested_;
  helpers::Event<void(int)> on_stage_;

  std::vector<VariableInfo> variables_;

public:
  VariableContainer(size_t size) {
    variables_.resize(size);
  }

  void insert(int variable_number, const types::SystemType& type, int priority, bool is_member, bool is_object_reference) {
    Variable* variable = gc_.add(new Variable(variable_number, type, priority, is_member, is_object_reference));
    variables_.at((size_t) variable_number).set_variable(variable);

    on_insert_requested_.update(variable_number);
    on_insert_.update(variable_number);
  }

  void persist_all() {
    for (VariableInfo& info : variables_) {
      if (info.contains_variable()) {
        persist(info.variable()->variable_number());
      }
    }
  }

  void persist(int variable_number) {
    validate_contains_variable(variable_number);

    on_persist_requested_.update(variable_number);
    on_persist_.update(variable_number);
  }

  void stage(int variable_number) {
    validate_contains_variable(variable_number);

    on_stage_requested_.update(variable_number);
    on_stage_.update(variable_number);
  }

  VariableInfo& at(int variable_number) {
    validate_contains_variable(variable_number);
    return variables_.at((size_t)variable_number);
  }

  void subscribe_on_insert_requested(std::function<void(int)> callback) {
    on_insert_requested_.add(callback);
  }

  void subscribe_on_persist_requested(std::function<void(int)> callback) {
    on_persist_requested_.add(callback);
  }

  void subscribe_on_stage_requested(std::function<void(int)> callback) {
    on_stage_requested_.add(callback);
  }

  void subscribe_on_insert(std::function<void(int)> callback) {
    on_insert_.add(callback);
  }

  void subscribe_on_persist(std::function<void(int)> callback) {
    on_persist_.add(callback);
  }

  void subscribe_on_stage(std::function<void(int)> callback) {
    on_stage_.add(callback);
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


#endif //__VariableContainer_H_
