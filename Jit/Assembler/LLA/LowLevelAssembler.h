//
// Created by Reuben Kuhnert on 14/8/2.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "JitEmitter.h"
#include "JitCodeSegment.h"

#ifndef __LowLevelAssembly_H_
#define __LowLevelAssembly_H_


namespace lla {
    class LowLevelAssembler {
        void* memory_;
        jit::JitEmitter emitter_;
        jit::JitCodeSegment segment_;

    public:
        LowLevelAssembler(byte* memory): memory_(memory), emitter_(memory) { }

        void ret() { segment_.ret(); }
        void render() { segment_.emit_to(emitter_); }

        void begin_frame() { segment_.begin_frame(); }
        void end_frame() { segment_.end_frame(); }

        void* memory() { return memory_; }

        jit::JitCodeSegment& segment() { return segment_; }
    };
}


#endif //__LowLevelAssembly_H_
