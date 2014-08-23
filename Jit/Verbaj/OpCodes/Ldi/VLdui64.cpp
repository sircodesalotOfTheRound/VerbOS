//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VLdui64.h"
#include "VerbajPrimitives.h"

void verbaj::VLdui64::apply(jit::VirtualRegisterStage &stage) const {
    using namespace jit;



    // Create a new virtual register and add it.
    VirtualRegister::Priority priority (1);
    VirtualRegister::Offset offset (1);

    VirtualRegister virtual_register { "v_reg", VerbajPrimitives::vm_uint64, priority, offset };
    stage.insert_at(register_index, virtual_register);

    // Perform the load
    stage.with_register(register_index, [&](jit::VirtualRegisterCheckoutRef checkout) {
        perform_load(checkout);
    });
}

void verbaj::VLdui64::perform_load(jit::VirtualRegisterCheckoutRef checkout) const {
    auto sys_register = checkout.sys_register();
    auto virt_register = checkout.virtual_register();
    auto& opcodes = checkout.opcodes();

    std::cout << "applying to register: " << sys_register << std::endl;

    // Move the value to the register. Done.
    opcodes.mov(sys_register, value_);
}
