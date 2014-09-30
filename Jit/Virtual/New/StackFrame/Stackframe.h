//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __Stackframe_H_
#define __Stackframe_H_

#include "VariableAllocator.h"

namespace jit {
  class Stackframe {
    op::ProcessorOpCodeSet jit_opcodes_;
    VariableAllocator allocator_;

  public:
    Stackframe(size_t max_objects, size_t max_constants);

    VariableAllocator& allocator();
    op::ProcessorOpCodeSet& jit_opcodes();
  };
}

#endif //__Stackframe_H_
