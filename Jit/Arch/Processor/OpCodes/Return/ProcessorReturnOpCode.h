//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorReturnOpCode_H_
#define __ProcessorReturnOpCode_H_

#include <iostream>
#include "TypeDef.h"
#include "ProcessorOpCodeBase.h"

namespace op {
  class ProcessorReturnOpCode : public ProcessorOpCodeBase {
  public:
    void render(jit::JitRenderer& renderer) const;
    size_t size() const;
    std::string rep() const;
  };
}


#endif //__ProcessorReturnOpCode_H_
