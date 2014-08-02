//
// Created by Reuben Kuhnert on 14-6-17.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "PushOpCode.h"

void opcodes::PushOpCode::render(jit::JitEmitter &writer) {
    switch (_operand.type()) {
        case Operand::REGISTER:
            writer.write_opcode_masked(0x50, _operand.reg());
            break;

        case Operand::CONSTANT:
            if (_operand.value() < 0xFF) {
                writer.write_opcode(0x6a);
                writer.write_int8((uint8)_operand.value());
            }
            else if (_operand.value() < 0xFFFFFFFF) {
                writer.write_opcode(0x68);
                writer.write_int32((uint32)_operand.value());
            }
            break;
    }
}
