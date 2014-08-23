//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "ProcessorOpCodeBase.h"

#ifndef __ProcessorPopOpCode_H_
#define __ProcessorPopOpCode_H_

namespace op {
    class ProcessorPopOpCode : public ProcessorOpCodeBase {
        const arch::CpuRegister& register_;

    public:
        ProcessorPopOpCode(const arch::CpuRegister& reg) : register_(reg) { }

        virtual std::string rep() const override { return "push"; };
        virtual size_t size() const override { return 1; }
        virtual void render(jit::JitRenderer& renderer) const override {
            renderer.write_opcode_masked(0x58, register_);
        };

    };
}


#endif //__ProcessorPopOpCode_H_
