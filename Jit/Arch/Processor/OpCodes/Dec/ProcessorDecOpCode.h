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

    size_t size() const override {
      return 3;
    }

    std::string rep() const override {
      return "inc";
    }

    void render(jit::JitRenderer& renderer) const override {
      renderer.write_preamble64lhs(sys_register_);
      renderer.write_opcode(0xFF);
      renderer.write_opcode_masked(0xc8, sys_register_);
    }

  };
}


#endif //__ProcessorDecOpCode_H_
