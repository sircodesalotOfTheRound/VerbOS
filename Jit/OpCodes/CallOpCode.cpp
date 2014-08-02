//
// Created by Reuben Kuhnert on 14-6-17.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "CallOpCode.h"

#include <iostream>
using namespace std;

void opcodes::CallOpCode::render(jit::JitEmitter &writer) {
    if (_operand.type() == Operand::REGISTER) {
        writer.write_opcode(0xff);
        writer.write_register_masked(0xd0, _operand.reg());
    }

    else if (_operand.type() == Operand::POINTER) {
        uintptr_t to_location = (uintptr_t)_operand.pointer();
        off_t offset = (to_location - (writer.current_address() + 5));

        writer.write_opcode(0xe8);
        writer.write_int32((int32) offset);
    }
}
