//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __ProcessorMovOpCode_H_
#define __ProcessorMovOpCode_H_

#include "ProcessorOpCodeBase.h"

namespace op {
    class ProcessorMovOpCode : public ProcessorOpCodeBase {
        size_t size() const override { return 5; }
        std::string rep() const override { return "mov"; }
        void render(jit::JitRenderer&) const override;
    };
}


#endif //__ProcessorMovOpCode_H_
