//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VirtualStackFrame.h"

void jit::VirtualStackFrame::apply(jit::JitRenderer& renderer) {
    // Clear the existing opcodes.
    jit_opcodes.clear();

    // Apply the Verbaj opcodes.
    for (auto &verbaj_op : verbaj_ops) {
        verbaj_op->apply(*this);
    }

    jit_opcodes.render(renderer);
}

void jit::VirtualStackFrame::debug_print() {
    // Clear the existing opcodes.
    jit_opcodes.debug_print();
}
