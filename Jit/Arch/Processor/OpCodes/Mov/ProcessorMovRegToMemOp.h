//
// Created by Reuben Kuhnert on 14/8/22.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "CpuRegister.h"
#include "JitRenderer.h"
#include "ProcessorOpCodeBase.h"

#ifndef __ProcessorMovRegToMemOp_H_
#define __ProcessorMovRegToMemOp_H_

namespace op {
  class ProcessorMovRegToMemOp : public ProcessorOpCodeBase {
  public:
    enum class DIRECTION {
      FROM_MEMORY,
      TO_MEMORY
    };

    ProcessorMovRegToMemOp(arch::ConstCpuRegisterRef reg,
      arch::DereferencedCpuRegister memory_location, DIRECTION direction)
      : register_(reg),
        memory_location_(memory_location),
        direction_(direction) {

    }

    size_t size() const;
    std::string rep() const;
    void render(jit::JitRenderer&) const override;

  private:
    DIRECTION direction_; // are we saving or reading from memory
    arch::CpuRegister register_;
    arch::DereferencedCpuRegister memory_location_;
  };
}


#endif //__ProcessorMovRegToMemOp_H_
