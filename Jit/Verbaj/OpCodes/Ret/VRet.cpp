//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VRet.h"
#include "StackFrame.h"

void verbaj::VRet::apply(jit::StackFrame &frame) const {
    auto& stage = frame.stage();

    std::cout << register_index_ << std::endl;

    stage.with_register(register_index_, [](jit::VirtualRegisterCheckoutRef checkout) {
        auto& sys_register = checkout.sys_register();
        auto& jit_opcodes = checkout.jit_opcodes();

        std::cout << sys_register << std::endl;

        jit_opcodes.mov(arch::OsxRegisters::rax, sys_register);
        jit_opcodes.ret();
    });
}
