//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ProcessorOpCodeSet_H_
#define __ProcessorOpCodeSet_H_

#include <vector>
#include <unordered_map>
#include "ProcessorOpCodeBase.h"

namespace op {
    class ProcessorOpCodeSet {
        using iterator = std::vector<std::unique_ptr<ProcessorOpCodeBase>>::iterator;

        std::vector<std::unique_ptr<ProcessorOpCodeBase>> op_codes_;

    public:
        void add(ProcessorOpCodeBase* op_code) {
            op_codes_.push_back(std::unique_ptr<ProcessorOpCodeBase>(op_code));
        }

        iterator begin() { return op_codes_.begin(); }
        iterator end() { return op_codes_.end(); }
    };
}


#endif //__ProcessorOpCodeSet_H_
