//
// Created by Reuben Kuhnert on 14/9/30.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorJumpOpCode_H_
#define __ProcessorJumpOpCode_H_

#include "ProcessorOpCodeBase.h"

namespace op {
  class ProcessorOpCodeSet;
  class ProcessorJumpOpCode : public ProcessorOpCodeBase {
    std::string name_;
    ProcessorOpCodeSet& jit_opcodes_;

  public:
    ProcessorJumpOpCode(std::string name, op::ProcessorOpCodeSet& jit_opcodes);

    std::string rep() const;
    size_t size() const;
    void render(jit::JitRenderer&) const;
  };
}


#endif //__ProcessorJumpOpCode_H_
