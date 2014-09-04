//
// Created by Reuben Kuhnert on 14/9/4.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VDeref.h"
#include "VirtualStackFrame.h"

void verbaj::VDeref::apply(jit::VirtualStackFrame& frame) const {
    auto& stage = frame.variable_stage();
    jit::VirtualVariable& variable = stage[variable_number_];

    //jit::VirtualVariable(child_number_,  const SystemType &type, int priority, bool is_member, bool is_class_pointer) :

    //variable.add_child();
}
