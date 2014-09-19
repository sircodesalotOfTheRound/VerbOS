//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "ProcessorOpCodeBase.h"

#ifndef __ProcessorPushOpCode_H_
#define __ProcessorPushOpCode_H_

namespace op {
  class ProcessorPushOpCode : public ProcessorOpCodeBase {
    const arch::CpuRegister& register_;

  public:
    ProcessorPushOpCode(const arch::CpuRegister& reg) : register_(reg) {
    }

    virtual std::string rep() const;
    virtual size_t size() const;
    virtual void render(jit::JitRenderer& renderer) const;;
  };
}


#endif //__ProcessorPushOpCode_H_
