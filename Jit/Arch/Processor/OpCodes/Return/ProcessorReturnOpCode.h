//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorReturnOpCode_H_
#define __ProcessorReturnOpCode_H_

#include <iosfwd>
#include "TypeDef.h"
#include "ProcessorOpCodeBase.h"

namespace op {
    class ProcessorReturnOpCode : public ProcessorOpCodeBase {
    public:
        size_t size() const override { return 1; }
        std::string rep() const override { return "ret"; }
    };
}


#endif //__ProcessorReturnOpCode_H_
