//
// Created by Reuben Kuhnert on 14/9/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VerbajOpCodeBase.h"

#ifndef __VBox_H_
#define __VBox_H_

namespace verbaj {
    class VBox : public VerbajOpCodeBase {
        int virtual_variable_index_;

    public:
        VBox(int virtual_variable_index) : virtual_variable_index_(virtual_variable_index) { }

        void apply(jit::VirtualStackFrame&) const;
    };
}


#endif //__VBox_H_
