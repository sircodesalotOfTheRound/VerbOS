//
// Created by Reuben Kuhnert on 14/8/25.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VStageArg.h"
#include "VirtualStackFrame.h"

void verbaj::VStageArg::apply(jit::VirtualStackFrame &frame) const {
    auto& stage = frame.variable_stage();
    auto & rdi = arch::OsxRegisters::rdi;

    stage.stage_argument(variable_number);
}
