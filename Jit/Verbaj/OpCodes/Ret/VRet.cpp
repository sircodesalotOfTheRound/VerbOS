//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VRet.h"
#include "VirtualStackFrame.h"

void verbaj::VRet::apply(jit::VirtualStackFrame &frame) const {
    auto& stage = frame.variable_stage();

    stage.with_register(register_index_, [](jit::VirtualVariableCheckout& checkout) {
        using namespace arch;

        auto& sys_register = checkout.sys_register();
        auto& jit_opcodes = checkout.jit_opcodes();

        // Mov return code to 'rax'. Then replace 'rbp'.
        jit_opcodes.mov(OsxRegisters::rax, sys_register);
        jit_opcodes.add(OsxRegisters::rsp, 512);
        jit_opcodes.pop(OsxRegisters::rbp);
        jit_opcodes.ret();
    });
}
