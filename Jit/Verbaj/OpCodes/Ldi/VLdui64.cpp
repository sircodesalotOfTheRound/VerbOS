//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VLdui64.h"
#include "VerbajPrimitives.h"

void verbaj::VLdui64::apply(jit::VirtualStackFrame & frame) const {
    using namespace jit;

    // Create a new virtual register and add it.
    auto& stage = frame.variable_stage();

    VirtualVariable variable { register_index, VerbajPrimitives::vm_uint64, 1, false };
    stage.new_local(std::move(variable));

    // Perform the load
    stage.with_register(register_index, [&](jit::VirtualVariableCheckout& checkout) {
        perform_load(checkout);
    });
}

void verbaj::VLdui64::perform_load(jit::VirtualVariableCheckout& checkout) const {
    auto sys_register = checkout.sys_register();
    op::ProcessorOpCodeSet& opcodes = checkout.jit_opcodes();

    // Move the value to the register. Done.
    opcodes.mov(sys_register, value_);
}
