//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorLabelOpCode_H_
#define __ProcessorLabelOpCode_H_

#include <string>
#include <sstream>
#include "ProcessorOpCodeBase.h"

namespace op {
  class ProcessorLabelOpCode : public ProcessorOpCodeBase {
    std::string name_;

  public:
    ProcessorLabelOpCode(std::string name) : name_(name) {
    }

    void render(jit::JitRenderer&) const override {
      /* NOP */
    }

    std::string rep() const override {
      std::stringstream representation;
      representation << "label: " << name_;

      return representation.str();
    }

    size_t size() const override {
      return 0;
    }
  };
}


#endif //__ProcessorLabelOpCode_H_
