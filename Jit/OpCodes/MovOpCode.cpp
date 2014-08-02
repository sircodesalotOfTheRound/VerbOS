//
// Created by Reuben Kuhnert on 14-6-11.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "MovOpCode.h"

void opcodes::MovOpCode::render(jit::JitEmitter &writer) {
    if (_lhs.type() == Operand::REGISTER) {
        if (_rhs.type() == Operand::REGISTER) {
            writer.write_opcode(0x89);
            writer.write_registers_masked(0xc0, _rhs.reg(), _lhs.reg());
        }
        else {
            writer.write_prefix64();
            writer.write_opcode_masked(0xb8, _lhs.reg());
            writer.write_int64(_rhs.value());
        }
    }

    if (_lhs.type() == Operand::POINTER) {
        if (_rhs.type() == Operand::REGISTER) {
            writer.write_prefix64();
            writer.write_opcode_masked(0xa3, _rhs.reg());
            writer.write_int64((uintptr_t) &*_lhs.pointer());
        }
    }
}
