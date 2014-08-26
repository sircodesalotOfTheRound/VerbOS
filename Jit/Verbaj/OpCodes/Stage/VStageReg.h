//
// Created by Reuben Kuhnert on 14/8/25.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VerbajOpCodeBase.h"

#ifndef __VStageReg_H_
#define __VStageReg_H_

namespace verbaj {
    class VStageReg : public VerbajOpCodeBase {
        int register_;

    public:
        virtual void apply(jit::VirtualStackFrame &);
    };
}


#endif //__VStageReg_H_
