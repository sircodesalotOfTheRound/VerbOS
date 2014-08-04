//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __GivenCallback_H_
#define __GivenCallback_H_

#include <functional>
#include "VariableComparison.h"
#include "HighLevelAssembler.h"

namespace hla {

    class HighLevelAssembler;
    template<class Comparison_Type>
    class GivenCallback {
    };

    template<>
    class GivenCallback<hla::VariableComparison> {
        const HighLevelAssembler& context_;

    public:
        GivenCallback(const HighLevelAssembler& context, hla::VariableComparison comparison) : context_(context) {
        }

        void operator()(std::function<void(const HighLevelAssembler&)> func);
    };
}

#endif //__GivenCallback_H_
