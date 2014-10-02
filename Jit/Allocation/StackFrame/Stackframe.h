//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __Stackframe_H_
#define __Stackframe_H_

#include "VariableAllocator.h"
#include "VerbajOpCodeBase.h"
#include "VerbajOpCodeSet.h"

namespace jit {
  class Stackframe {
    verbaj::VerbajOpCodeSet verbaj_ops;
    op::ProcessorOpCodeSet jit_opcodes_;
    VariableAllocator allocator_;

  public:
    Stackframe(size_t max_objects, size_t max_constants);

    VariableAllocator& allocator();
    op::ProcessorOpCodeSet& jit_opcodes();

    void insert(verbaj::VerbajOpCodeBase* opcode) {
      verbaj_ops.add(opcode);
    }

    void apply(jit::JitRenderer& renderer);

    verbaj::VerbajOpCodeSet& opcodes() {
      return verbaj_ops;
    }

    op::ProcessorOpCodeSet& sys_ops() {
      return jit_opcodes_;
    }

    void debug_print();

  private:

  };
}

#endif //__Stackframe_H_
