//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorRegToRegMovOp.h"

void op::ProcessorRegToRegMovOp::render(jit::JitRenderer &renderer) const {
    if (lhs_.is_extended() || rhs_.is_extended()) {
        renderer.write_extension_preamble(lhs_, rhs_);
    }

    renderer.write_preamble64();
    renderer.write_opcode(0x89);

    // Note op-code is backwards
    renderer.write_opcode_masked(0xc0, rhs_, lhs_);
}
