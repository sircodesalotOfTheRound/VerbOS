//
// Created by Reuben Kuhnert on 14/8/2.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "RegisterBinding.h"
#include "Variable.h"

hla::Variable &sysarch::RegisterBinding::variable() { return *variable_; }

void sysarch::RegisterBinding::variable(hla::Variable& variable) {
    variable_ = &variable;
    priority_ = variable.priority();
}

std::ostream& sysarch::operator<<(std::ostream& stream, const RegisterBinding& binding) {
    return stream << (*binding.register_);
}