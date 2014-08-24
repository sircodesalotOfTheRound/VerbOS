//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorSubConstToRegOpCode.h"

void op::ProcessorSubConstToRegOpCode::render(jit::JitRenderer &renderer) const {
    renderer.write_preamble64lhs(lhs_);

    renderer.write_opcode(0x81);
    renderer.write_opcode_masked(0xc0, lhs_);

    // Add only comes in 32 bit variant
    renderer.write_int32((uint32_t)-rhs_);
}