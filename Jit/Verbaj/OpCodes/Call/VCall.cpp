//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VCall.h"
#include "VirtualStackFrame.h"

void verbaj::VCall::apply(jit::VirtualStackFrame &frame) const {
    frame.sys_ops().call(location_);
}
