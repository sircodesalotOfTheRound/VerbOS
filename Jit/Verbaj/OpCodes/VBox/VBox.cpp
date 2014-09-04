//
// Created by Reuben Kuhnert on 14/9/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VBox.h"
#include "VirtualStackFrame.h"

void verbaj::VBox::apply(jit::VirtualStackFrame& frame) const {
    auto& stage = frame.variable_stage();

    if (!stage.contains_variable(virtual_variable_index_)) {
        throw std::logic_error("stage does not contain a variable at this index.");
    }

    auto& virtual_variable = stage[virtual_variable_index_];
    std::cout << virtual_variable.type() << std::endl;
}
