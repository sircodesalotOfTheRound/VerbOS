//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __JitRenderer_H_
#define __JitRenderer_H_

#include "TypeDef.h"

namespace jit {
    class JitRenderer {
        byte* memory_;
        off_t write_offset_;

    public:
        JitRenderer(void* memory) : memory_((byte*)memory), write_offset_(0) { }

        void write_opcode(byte data) {
            memory_[write_offset_++] = data;
        }

        void* memory() { return memory_;}
    };
}


#endif //__JitRenderer_H_
