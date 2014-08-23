//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorMovOpCode.h"

void op::RegToRegProcessorMovOpCode::render(jit::JitRenderer &renderer) const {

}

void op::ConstToRegProcessorMovOpCode::render(jit::JitRenderer &renderer) const {
    renderer.write_opcode_masked(0xb8, *lhs_);
    renderer.write_int32(static_cast<uint32_t>(rhs_));

}
