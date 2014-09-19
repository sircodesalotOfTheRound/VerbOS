//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorAddOpCode_H_
#define __ProcessorAddOpCode_H_

#include "ProcessorOpCodeBase.h"

namespace op {
  class ProcessorAddRegToRegOpCode : public ProcessorOpCodeBase {
    arch::CpuRegister lhs_;
    arch::CpuRegister rhs_;

  public:
    ProcessorAddRegToRegOpCode(const arch::CpuRegister& lhs, const arch::CpuRegister& rhs) : lhs_(lhs), rhs_(rhs) { }

    std::string rep() const;;
    size_t size() const;
    void render(jit::JitRenderer&) const;
  };
}


#endif //__ProcessorAddOpCode_H_
