//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "ProcessorOpCodeBase.h"

#ifndef __ProcessorPopOpCode_H_
#define __ProcessorPopOpCode_H_

namespace op {
  class ProcessorPopOpCode : public ProcessorOpCodeBase {
    const arch::CpuRegister& register_;

  public:
    ProcessorPopOpCode(const arch::CpuRegister& reg) : register_(reg) {
    }

    std::string rep() const;;
    size_t size() const;
    void render(jit::JitRenderer& renderer) const;;

  };
}


#endif //__ProcessorPopOpCode_H_
