//
// Created by Reuben Kuhnert on 14-6-21.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#ifndef __JitVirtualCallFrame_H_
#define __JitVirtualCallFrame_H_

#include "JitStackFrameTemplate.h"
#include "VerboseString.h"

namespace jit {
    class JitVirtualCallFrame : JitStackFrameTemplate {
        VerboseString signature_;
        size_t parameters_;
        size_t locals_;
        size_t exceptions_;

        JitVirtualCallFrame(vm::ExecutionEnvironment & environment,
                VerboseString& signature_,
                VerboseString& return_type,
                size_t parameters,
                size_t locals,
                size_t exceptions)
            : signature_(signature_), parameters_(parameters), locals_(locals), exceptions_(exceptions)
        {

        }


       /*void operations(JitCodeSegment& segment) {
           lit::VirtualRegisterSet register_set;
           operations(register_set);
       }*/

    protected:
        virtual void config() = 0;
        //virtual void operations(lit::VirtualRegisterSet& frame) = 0;
    };
}


#endif //__JitVirtualCallFrame_H_
