//
// Created by Reuben Kuhnert on 14/9/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VerbajOpCodeBase.h"
#include "Instance.h"

#ifndef __VBox_H_
#define __VBox_H_

namespace verbaj {
    class VBox : public VerbajOpCodeBase {
        int variable_number_;

    public:
        VBox(int virtual_variable_index) : variable_number_(virtual_variable_index) { }

        void apply(jit::VirtualStackFrame&) const;

    private:
        static types::Trait* instantiate(uint64_t value);
    };
}


#endif //__VBox_H_
