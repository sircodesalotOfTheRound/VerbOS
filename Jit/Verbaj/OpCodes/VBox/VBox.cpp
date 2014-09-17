//
// Created by Reuben Kuhnert on 14/9/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VBox.h"
#include "VirtualStackFrame.h"
#include "VerbajPrimitives.h"
#include "Instance.h"

void verbaj::VBox::apply(jit::VirtualStackFrame& frame) const {
    auto& stage = frame.variable_stage();

    if (!stage.contains_variable(variable_number_)) {
        throw std::logic_error("stage does not contain a variable at this index.");
    }

    auto& virtual_variable = stage[variable_number_];

    std::cout << virtual_variable.type() << std::endl;
    std::cout << virtual_variable.variable_number() << std::endl;

    stage.stage_argument(variable_number_);
    stage.persist_variables();
    frame.sys_ops().call(&instantiate);

}

void verbaj::VBox::instantiate(uint64_t value) {
    std::cout << "boxing: " << value << std::endl;
    types::Instance* instance = new (VerbajPrimitives::vm_uint64) types::Instance;
    instance->head().data<uint64_t>()[0] = value;

    std::cout << "@" << instance << std::endl;
}
