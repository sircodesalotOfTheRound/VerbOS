//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ProcessorIncOpCode_H_
#define __ProcessorIncOpCode_H_

#include "ProcessorOpCodeBase.h"
#include <iostream>

namespace op {
    class ProcessorIncOpCode : public ProcessorOpCodeBase {
        const arch::CpuRegister sys_register_;

    public:
        ProcessorIncOpCode(const arch::CpuRegister& sys_register) :
            sys_register_(sys_register)
        {

        }

        size_t size() const override { return 3; }
        std::string rep() const override { return "inc"; }

        void render(jit::JitRenderer& renderer) const override {
            renderer.write_preamble64();
            renderer.write_opcode(0xFF);
            renderer.write_opcode_masked(0xc0, sys_register_);
        }

    };
}


#endif //__ProcessorIncOpCode_H_
