//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "HighLevelAssembler.h"

hla::GivenCallback<hla::VariableComparison> hla::HighLevelAssembler::given(const hla::VariableComparison comparison) {
    return GivenCallback<VariableComparison>(*this, comparison);
}