//
// Created by Reuben Kuhnert on 14/10/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorCmpOpCode_H_
#define __ProcessorCmpOpCode_H_

#include "ProcessorOpCodeBase.h"

namespace op {
  class ProcessorCmpOpCode : public ProcessorOpCodeBase {
    const arch::CpuRegister& lhs_;
    const arch::CpuRegister& rhs_;

  public:
    ProcessorCmpOpCode(const arch::CpuRegister& lhs, const arch::CpuRegister& rhs);

    std::string rep() const override;
    size_t size() const override;
    void render(jit::JitRenderer&) const override;
  };
}


#endif //__ProcessorCmpOpCode_H_
