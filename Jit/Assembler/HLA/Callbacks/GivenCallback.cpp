//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "GivenCallback.h"

void hla::GivenCallback<hla::VariableComparison>::operator()(std::function<void(const HighLevelAssembler&)> func) {
    std::cout << "calling the function" << std::endl;
    func(context_);
}