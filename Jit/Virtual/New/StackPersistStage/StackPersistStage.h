//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __StackPersistStage_H_
#define __StackPersistStage_H_

#include "VariableContainer.h"

class StackPersistStage {
  VariableContainer& container_;

public:
  StackPersistStage(VariableContainer& container): container_(container) {
    container_.subscribe_on_persist([&](int variable_number){
      persist_variable(variable_number);
    });
  }

private:
  void persist_variable(int variable_number) {
    std::cout << "now persisting variable: " << variable_number << std::endl;
    VariableInfo& info = container_.at(variable_number);

    if (info.is_register_bound()) {
      std::cout << "clearing from register: " << *info.bound_register() << std::endl;
      info.clear_register_binding();
    }
  }
};


#endif //__StackPersistStage_H_
