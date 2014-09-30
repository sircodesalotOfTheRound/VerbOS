//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "Stackframe.h"


jit::Stackframe::Stackframe(size_t max_objects, size_t max_constants):
  allocator_(max_objects, max_constants, jit_opcodes_)
{

}

jit::VariableAllocator& jit::Stackframe::allocator() {
  return allocator_;
}

op::ProcessorOpCodeSet& jit::Stackframe::jit_opcodes() {
  return jit_opcodes_;
}
