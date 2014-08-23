//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "ProcessorOpCodeBase.h"

#ifndef __ProcessorPushOpCode_H_
#define __ProcessorPushOpCode_H_

namespace op {
    class ProcessorPushOpCode : public ProcessorOpCodeBase {
        const arch::CpuRegister& register_;

    public:
        ProcessorPushOpCode(const arch::CpuRegister& reg) : register_(reg) { }

        virtual std::string rep() const override { return "push"; };
        virtual size_t size() const override { return 1; }
        virtual void render(jit::JitRenderer& renderer) const override {
            renderer.write_opcode_masked(0x50, register_);
        };
    };
}


#endif //__ProcessorPushOpCode_H_
