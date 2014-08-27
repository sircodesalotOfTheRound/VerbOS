//
// Created by Reuben Kuhnert on 14/8/25.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VerbajOpCodeBase.h"

#ifndef VSTAGE_ARG_H
#define VSTAGE_ARG_H

namespace verbaj {
    class VStageReg : public VerbajOpCodeBase {
        int virutal_register_;

    public:
        VStageReg(int virtual_register) : virutal_register_(virtual_register) { }

        void apply(jit::VirtualStackFrame &) const;
    };
}


#endif // VSTAGE_ARG_H
