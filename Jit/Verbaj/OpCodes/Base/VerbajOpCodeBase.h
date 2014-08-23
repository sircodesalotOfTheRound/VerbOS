//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "JitRenderer.h"
#include "VirtualRegisterStage.h"

#ifndef __VerbajOpCode_H_
#define __VerbajOpCode_H_

namespace verbaj {
    class VerbajOpCodeBase {
    public:
        virtual ~VerbajOpCodeBase() { }

        virtual void render(jit::VirtualRegisterStage&) const = 0;

    };
}


#endif //__VerbajOpCode_H_
