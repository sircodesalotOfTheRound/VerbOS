//
// Created by Reuben Kuhnert on 14-6-19.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "SubOpCode.h"

void opcodes::SubOpCode::render(jit::JitEmitter &writer) {
    if (_rhs.type() == Operand::REGISTER) {
        writer.write_prefix64();
        writer.write_opcode(0x29);
        writer.write_registers_masked(0xc0, _rhs.reg(), _lhs.reg());
    }
}
