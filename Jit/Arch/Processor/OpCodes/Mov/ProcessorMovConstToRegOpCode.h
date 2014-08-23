//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __ProcessorMovOpCode_H_
#define __ProcessorMovOpCode_H_

#include "ProcessorOpCodeBase.h"
#include "ProcessorOpCodeOperand.h"

namespace op {
    class ProcessorMovConstToRegOpCode : public ProcessorOpCodeBase {
        arch::ConstCpuRegisterRef lhs_;
        uint64_t rhs_;

    public:
        ProcessorMovConstToRegOpCode(const arch::CpuRegister& lhs, uint64_t rhs) :
            lhs_(lhs), rhs_(rhs) {

        }

    public:
        size_t size() const override { return 5; }
        std::string rep() const override { return "mov"; }
        void render(jit::JitRenderer&) const override;
    };
}


#endif //__ProcessorMovOpCode_H_
