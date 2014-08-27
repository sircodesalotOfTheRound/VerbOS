//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __StackFrame_H_
#define __StackFrame_H_

#include "JitRenderer.h"
#include "ProcessorOpCodeSet.h"
#include "VirtualRegisterStage.h"
#include "VerbajOpCodeSet.h"

namespace verbaj {
    class VerbajOpCodeBase;
}

namespace jit {
    class VirtualStackFrame {
        verbaj::VerbajOpCodeSet verbaj_ops;
        op::ProcessorOpCodeSet jit_opcodes;
        jit::VirtualRegisterStage register_stage_;

    public:
        VirtualStackFrame()
            : register_stage_(0, jit_opcodes)
        {

        }

        void insert(verbaj::VerbajOpCodeBase *opcode) {
            verbaj_ops.add(opcode);
        }

        void apply(jit::JitRenderer& renderer);

        verbaj::VerbajOpCodeSet& opcodes() { return verbaj_ops; }
        op::ProcessorOpCodeSet& sys_ops() { return jit_opcodes; }
        VirtualRegisterStage&register_stage() { return register_stage_; }

        void debug_print();

        void stage_argument(int virtual_register) {
            register_stage_.stage_argument(virtual_register);
        }
        size_t staged_argument_count() { return register_stage_.staged_argument_count(); }
    private:

    };
}


#endif //__StackFrame_H_
