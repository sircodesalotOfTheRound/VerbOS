//
// Created by Reuben Kuhnert on 14-6-19.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "AddOpCode.h"
#include <stdexcept>

void opcodes::AddOpCode::render(jit::JitEmitter &writer) {
    if (_rhs.type() == Operand::REGISTER) {
        writer.write_prefix64();
        writer.write_opcode(0x01);
        writer.write_registers_masked(0xc0, _rhs.reg(), _lhs.reg());
    }

    else if (_rhs.type() == Operand::CONSTANT) {
        uint64 value = _rhs.value();

        if (value < 128) {
            writer.write_prefix64();
            writer.write_opcode(0x83);
            writer.write_register_masked(0xc0, _lhs.reg());
            writer.write_int8((uint8)value);
        }
        else if (value < 65535) {
            writer.write_prefix64();
            writer.write_opcode(0x81);
            writer.write_register_masked(0xc0, _lhs.reg());
            writer.write_int32((int32)value);
        }
        else {
            throw std::invalid_argument("bad size");
        }
    }
}
