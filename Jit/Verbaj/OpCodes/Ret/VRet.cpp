//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VRet.h"
#include "VirtualStackFrame.h"

void verbaj::VRet::apply(jit::VirtualStackFrame &frame) const {
    auto& stage = frame.stage();

    stage.with_register(register_index_, [](jit::VirtualRegisterCheckoutRef checkout) {
        auto& sys_register = checkout.sys_register();
        auto& jit_opcodes = checkout.jit_opcodes();

        jit_opcodes.mov(arch::OsxRegisters::rax, sys_register);
        jit_opcodes.ret();
    });
}
