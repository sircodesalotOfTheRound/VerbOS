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
    else if (_rhs.type() == Operand::CONSTANT) {
        // Subtract is the same op-code as add (just with a negative).
        int64 inverted_value = -(_rhs.value());

        if (inverted_value < 128) {
            writer.write_prefix64();
            writer.write_opcode(0x83);
            writer.write_register_masked(0xc0, _lhs.reg());
            writer.write_int8((uint8)inverted_value );
        }
        else if (inverted_value < 65535) {
            writer.write_prefix64();
            writer.write_opcode(0x81);
            writer.write_register_masked(0xc0, _lhs.reg());
            writer.write_int32((int32)inverted_value );
        }
        else {
            throw std::invalid_argument("bad size");
        }
    }
}
