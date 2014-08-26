//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorCallOpCode_H_
#define __ProcessorCallOpCode_H_

#include "ProcessorOpCodeBase.h"

namespace op {
    class ProcessorCallOpCode : public ProcessorOpCodeBase {
        uintptr_t location_;

    public:
        ProcessorCallOpCode(void* location) : location_((uintptr_t)&*location) { }

        std::string rep() const { return "call"; }
        size_t size() const { return 5; }
        void render(jit::JitRenderer&) const;
    };
}


#endif //__ProcessorCallOpCode_H_
