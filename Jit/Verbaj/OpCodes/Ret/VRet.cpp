//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VRet.h"
#include "VirtualStackFrame.h"

void verbaj::VRet::apply(jit::VirtualStackFrame& frame) const {
  auto& stage = frame.variable_stage();

  stage.with_register(register_index_, [](jit::VirtualVariableCheckout& checkout) {
    using namespace arch;

    auto& sys_register = checkout.sys_register();
    auto& jit_opcodes = checkout.jit_opcodes();

    // Mov return code to 'rax'. Then replace 'rbp'.
    jit_opcodes.mov(Intelx64Registers::rax, sys_register);
    jit_opcodes.add(Intelx64Registers::rsp, 256);
    jit_opcodes.pop(Intelx64Registers::rbp);
    jit_opcodes.ret();
  });
}

verbaj::VRet* verbaj::VRet::load_op(std::istream& stream) {
  return new VRet(0);
}
