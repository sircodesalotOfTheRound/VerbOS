//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorCallOpCode_H_
#define __ProcessorCallOpCode_H_

#include "ProcessorOpCodeBase.h"

namespace op {
  class ProcessorCallOpCode : public ProcessorOpCodeBase {
    uintptr_t location_;

    // TODO: Fix this
    mutable uint32_t call_offset_;

  public:
    ProcessorCallOpCode(void* location) : location_((uintptr_t) &*location) { }

    std::string rep() const;
    size_t size() const;
    void render(jit::JitRenderer&) const;
  };
}


#endif //__ProcessorCallOpCode_H_
