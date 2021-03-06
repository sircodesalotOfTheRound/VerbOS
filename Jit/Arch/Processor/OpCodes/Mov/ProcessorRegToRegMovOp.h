//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "ProcessorOpCodeBase.h"

#ifndef __ProcessorRegToRegMovOp_H_
#define __ProcessorRegToRegMovOp_H_

namespace op {
  class ProcessorRegToRegMovOp : public ProcessorOpCodeBase {
    arch::CpuRegister lhs_;
    arch::CpuRegister rhs_;

  public:
    ProcessorRegToRegMovOp(arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs) : lhs_(lhs), rhs_(rhs) {

    }

    size_t size() const;
    std::string rep() const;
    void render(jit::JitRenderer&) const override;
  };
}


#endif //__ProcessorRegToRegMovOp_H_
