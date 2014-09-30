//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorLabelOpCode_H_
#define __ProcessorLabelOpCode_H_

#include <string>
#include <sstream>
#include "ProcessorOpCodeBase.h"
#include "Event.h"

namespace op {
  class ProcessorOpCodeSet;
  class ProcessorLabelOpCode : public ProcessorOpCodeBase {
    std::string name_;
    op::ProcessorOpCodeSet& jit_opcodes_;

  public:
    ProcessorLabelOpCode(std::string name, op::ProcessorOpCodeSet& jit_opcodes);

    void render(jit::JitRenderer&) const;

    std::string rep() const;
    size_t size() const;
  };
}


#endif //__ProcessorLabelOpCode_H_
