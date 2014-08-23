//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "StackFrame.h"

void jit::StackFrame::apply(jit::JitRenderer& renderer) {
    // Clear the existing opcodes.
    jit_opcodes.clear();

    // Apply the Verbaj opcodes.
    for (auto &verbaj_op : verbaj_ops) {
        verbaj_op->apply(*this);
    }

    jit_opcodes.render(renderer);
}

