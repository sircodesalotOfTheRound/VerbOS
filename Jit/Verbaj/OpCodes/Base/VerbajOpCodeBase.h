//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __VerbajOpCode_H_
#define __VerbajOpCode_H_

#include "JitRenderer.h"
#include "VirtualRegisterStage.h"

namespace jit {
    class StackFrame;
}

namespace verbaj {
    class VerbajOpCodeBase {
    public:
        virtual ~VerbajOpCodeBase() { }

        virtual void apply(jit::StackFrame&) const = 0;
    };
}


#endif //__VerbajOpCode_H_
