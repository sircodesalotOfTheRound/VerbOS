//
// Created by Reuben Kuhnert on 14-6-11.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "ReturnOpCode.h"

void opcodes::ReturnOpCode::render(jit::JitEmitter & writer) {
    writer.write_opcode(0xc3);
}

size_t opcodes::ReturnOpCode::size() {
    return 1;
}