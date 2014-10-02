//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "Variable.h"

jit::Variable::Variable(int variable_number, const types::SystemType& type, int priority, bool is_member, bool is_object_reference)
  : variable_number_(variable_number),
    type_(type),
    priority_(priority),
    is_member_(is_member),
    is_object_reference_(is_object_reference) {

}

bool jit::Variable::is_object_reference() const { return is_object_reference_; }
bool jit::Variable::is_member() const { return is_member_; }
const types::SystemType& jit::Variable::type() const { return type_; }
int jit::Variable::variable_number() const { return variable_number_; }
int jit::Variable::priority() const { return priority_; }

