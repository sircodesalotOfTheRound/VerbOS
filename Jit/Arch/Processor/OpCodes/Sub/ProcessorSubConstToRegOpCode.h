//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorSubConstToRegOpCode_H_
#define __ProcessorSubConstToRegOpCode_H_


#include "ProcessorOpCodeBase.h"

namespace op {
  class ProcessorSubConstToRegOpCode : public ProcessorOpCodeBase {
    arch::CpuRegister lhs_;
    uint64_t rhs_;

  public:
    ProcessorSubConstToRegOpCode(const arch::CpuRegister& lhs, uint64_t value) : lhs_(lhs), rhs_(value) { }

    std::string rep() const;;
    size_t size() const;
    void render(jit::JitRenderer&) const override;
  };
}


#endif //__ProcessorSubConstToRegOpCode_H_
