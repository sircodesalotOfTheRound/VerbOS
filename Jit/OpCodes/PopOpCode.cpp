//
// Created by Reuben Kuhnert on 14-6-17.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "PopOpCode.h"

void opcodes::PopOpCode::render(jit::JitEmitter &writer) {
    writer.write_opcode_masked(0x58, _operand.reg());
}
