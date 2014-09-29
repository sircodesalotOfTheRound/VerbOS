//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __RegisterStage_H_
#define __RegisterStage_H_

#include "VariableContainer.h"
#include <unordered_set>


class RegisterStage {
  VariableContainer& container_;
  std::unordered_set<int> staged_indecies_;

public:
  RegisterStage(VariableContainer& container) :
    container_(container)
  {
    container_.subscribe_on_stage_requested([&](int variable_number) {
      on_request_stage(variable_number);
    });

    container.subscribe_on_variable_inserted([&](int variable_number){
      unstage_variable(variable_number);
    });
  }

public:
  bool is_staged(int variable_number) {
    return staged_indecies_.find(variable_number) != staged_indecies_.end();
  }

private:
  void on_request_stage(int variable_number) {
    using namespace std;

    // Do nothing if already staged.
    if (is_staged(variable_number)) {
      return;
    }

    cout << "requesting stage for: " << variable_number << endl;
    VariableInfo& info = container_.at(variable_number);
    cout << info.contains_variable() << endl;
  }

  void unstage_variable(int variable_number) {
    if (is_staged(variable_number)) {
      staged_indecies_.erase(variable_number);
    }
  }
};


#endif //__RegisterStage_H_
