//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __VirtualStackFrameRegisterSet_H_
#define __VirtualStackFrameRegisterSet_H_

#include <vector>
#include "VirtualRegister.h"

namespace jit {
    class VirtualStackFrameRegisterSet {
        std::vector<VirtualRegister> registers_;
        size_t parameters_;
        size_t locals_;
        size_t constants_;
        size_t objects_;
        size_t total_;

    public:
        VirtualStackFrameRegisterSet(size_t parameters, size_t locals, size_t constants, size_t objects) :
            parameters_(parameters), locals_(locals), constants_(constants), objects_(objects),
            total_(parameters + locals + constants + objects)
        {
            registers_.reserve(total_);

            for (int index = 0; index != total_; ++index) {
                registers_[index] = VirtualRegister::EMPTY;
            }
        }

        VirtualRegister& operator[](int index) { return registers_[index]; }

        int total() const { return total_; }
        int parameters() const { return parameters_; }
        int locals() const { return parameters_; }
        int constants() const { return constants_; }
        int objects() const { return objects_; }
    };
}


#endif //__VirtualStackFrameRegisterSet_H_
