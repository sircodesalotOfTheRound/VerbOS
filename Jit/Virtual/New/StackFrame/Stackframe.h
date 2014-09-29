//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VariableAllocator.h"

#ifndef __Stackframe_H_
#define __Stackframe_H_


class Stackframe {
  op::ProcessorOpCodeSet jit_opcodes_;
  VariableAllocator allocator_;

public:
  Stackframe(size_t size) : allocator_(size, jit_opcodes_)
  {

  }

  VariableAllocator& allocator() { return allocator_; }
};


#endif //__Stackframe_H_
