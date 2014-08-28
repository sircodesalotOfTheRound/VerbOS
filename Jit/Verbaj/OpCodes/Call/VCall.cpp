//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VCall.h"
#include "VirtualStackFrame.h"

void verbaj::VCall::apply(jit::VirtualStackFrame &frame) const {
    frame.sys_ops().call(location_);

    // Since we need to lock arguments to certain registers, (arg1=rdi, arg2=rsi, etc..)
    // We need to free those registers so they can be used generally.
    frame.variable_stage().unlock_argument_bindings();
}
