//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ProcessorIncOpCode_H_
#define __ProcessorIncOpCode_H_

#include "ProcessorOpCodeBase.h"
#include <iostream>

namespace op {
  class ProcessorIncOpCode : public ProcessorOpCodeBase {
    const arch::CpuRegister sys_register_;

  public:
    ProcessorIncOpCode(const arch::CpuRegister& sys_register) :
      sys_register_(sys_register) {

    }

    size_t size() const;
    std::string rep() const;
    void render(jit::JitRenderer& renderer) const;

  };
}


#endif //__ProcessorIncOpCode_H_
