//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __RegisterStage_H_
#define __RegisterStage_H_

#include "VariableContainer.h"
#include "OsxRegisters.h"
#include <unordered_set>


class RegisterStage {
  VariableContainer& container_;

public:
  RegisterStage(VariableContainer& container) :
    container_(container)
  {
    container_.subscribe_on_stage([&](int variable_number) {
      on_request_stage(variable_number);
    });

    container.subscribe_on_insert_requested([&](int variable_number) {
      unstage_variable(variable_number);
    });
  }

public:
  bool is_staged(int variable_number) {
    return container_.at(variable_number).is_register_bound();
  }

private:
  void on_request_stage(int variable_number) {
    using namespace std;

    // Do nothing if already staged.
    if (!is_staged(variable_number)) {
      VariableInfo& info = container_.at(variable_number);
      info.set_register_binding(&arch::OsxRegisters::rax);

      cout << "staged to: " << arch::OsxRegisters::rax << endl;
    } else {
      cout << "already staged " << endl;
    }
  }

  void unstage_variable(int variable_number) {
    if (is_staged(variable_number)) {
      container_.at(variable_number).is_register_bound();
    }
  }
};


#endif //__RegisterStage_H_
