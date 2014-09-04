//
// Created by Reuben Kuhnert on 14/9/4.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VerbajOpCodeBase.h"

#ifndef __VDeref_H_
#define __VDeref_H_

namespace verbaj {
    class VDeref : public VerbajOpCodeBase {
        int variable_number_;
        int child_number_;
        int offset_;

    public:

        void apply(jit::VirtualStackFrame &) const;
    };
}


#endif //__VDeref_H_
