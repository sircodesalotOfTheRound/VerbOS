//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __StackFrame_H_
#define __StackFrame_H_

#include "JitRenderer.h"
#include "ProcessorOpCodeSet.h"
#include "VerbajOpCodeSet.h"
#include "VirtualVariableStagingAllocator.h"

namespace verbaj {
    class VerbajOpCodeBase;
}

namespace jit {
    class VirtualStackFrame {
        verbaj::VerbajOpCodeSet verbaj_ops;
        op::ProcessorOpCodeSet jit_opcodes;
        jit::VirtualVariableStagingAllocator variable_stage_;

    public:
        VirtualStackFrame(size_t max_variable_count)
            : variable_stage_(jit_opcodes, max_variable_count)
        {

        }

        void insert(verbaj::VerbajOpCodeBase *opcode) {
            verbaj_ops.add(opcode);
        }

        void apply(jit::JitRenderer& renderer);

        verbaj::VerbajOpCodeSet& opcodes() { return verbaj_ops; }
        op::ProcessorOpCodeSet& sys_ops() { return jit_opcodes; }
        VirtualVariableStagingAllocator& variable_stage() { return variable_stage_; }

        void debug_print();
    private:

    };
}


#endif //__StackFrame_H_
