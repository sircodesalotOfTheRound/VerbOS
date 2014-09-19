//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ProcessorDecOpCode_H_
#define __ProcessorDecOpCode_H_

#include "ProcessorOpCodeBase.h"
#include <iostream>

namespace op {
  class ProcessorDecOpCode : public ProcessorOpCodeBase {
    const arch::CpuRegister sys_register_;

  public:
    ProcessorDecOpCode(const arch::CpuRegister& sys_register) :
      sys_register_(sys_register) {

    }

    size_t size() const;
    std::string rep() const;
    void render(jit::JitRenderer& renderer) const;

  };
}


#endif //__ProcessorDecOpCode_H_
