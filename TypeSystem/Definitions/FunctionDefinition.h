//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __FunctionDefinition_H_
#define __FunctionDefinition_H_

#include <cstddef>

namespace typesys {
    class FunctionDefinition {
        const size_t num_locals_;

    public:
        FunctionDefinition(size_t num_locals) : num_locals_(num_locals) { }
        const size_t num_locals() const { return num_locals_; }
    };
}


#endif //__FunctionDefinition_H_
