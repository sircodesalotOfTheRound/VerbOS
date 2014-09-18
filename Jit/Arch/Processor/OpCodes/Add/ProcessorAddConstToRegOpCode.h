//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __ProcessorAddConstToRegOpCode_H_
#define __ProcessorAddConstToRegOpCode_H_

#include "ProcessorOpCodeBase.h"

namespace op {
  class ProcessorAddConstToRegOpCode : public ProcessorOpCodeBase {
    arch::CpuRegister lhs_;
    uint64_t rhs_;

  public:
    ProcessorAddConstToRegOpCode(const arch::CpuRegister& lhs, uint64_t value) : lhs_(lhs), rhs_(value) {
    }

    std::string rep() const override {
      std::stringstream rep;
      rep << "add " << lhs_ << ", " << rhs_;

      return rep.str();
    };

    size_t size() const override {
      return 5;
    }

    void render(jit::JitRenderer&) const override;
  };
}


#endif //__ProcessorAddConstToRegOpCode_H_
