//
// Created by Reuben Kuhnert on 14-6-18.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "MovDerefOpcode.h"

void opcodes::MovDerefOpcode::render(jit::JitEmitter &writer) {
    if (offset_ == 0) {
        if (dereference_ == DEREF_DESTINATION) {
            writer.write_prefix64();
            writer.write_opcode(0x89);
            writer.write_registers_masked(0x00, rhs_.reg(), lhs_.reg());
        }
        else {
            writer.write_prefix64();
            writer.write_opcode(0x8b);
            writer.write_registers_masked(0x00, lhs_.reg(), rhs_.reg());
        }
    }
    else {
        if (dereference_ == DEREF_SOURCE) {
            writer.write_prefix64();
            writer.write_opcode(0x8b);
            writer.write_registers_masked(0x40, lhs_.reg(), rhs_.reg());
            writer.write_int8((int8) offset_);
        }
        else {
            writer.write_prefix64();
            writer.write_opcode(0x89);
            writer.write_registers_masked(0x40, rhs_.reg(), lhs_.reg());
            writer.write_int8((int8) offset_);
        }
    }
}
