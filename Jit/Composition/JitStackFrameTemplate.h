//
// Created by Reuben Kuhnert on 14-6-20.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#ifndef __JitStackFrame_H_
#define __JitStackFrame_H_

#include <functional>
#include "JitEmitter.h"
#include "JitCodeSegment.h"

namespace jit {
    class JitEmitter;
    class JitStackFrameTemplate {

    public:
        JitStackFrameTemplate() { }

        void* emit_to(JitEmitter &emitter);

    protected:
        virtual void operations(JitCodeSegment& segment) = 0;

    };
}


#endif //__JitStackFrame_H_
