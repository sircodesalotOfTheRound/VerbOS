//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorCallOpCode_H_
#define __ProcessorCallOpCode_H_

#include "ProcessorOpCodeBase.h"
//#include "VCall.h"

namespace op {
  class ProcessorCallOpCode : public ProcessorOpCodeBase {
    uintptr_t static_location_;
    std::string function_name_;

    // TODO: Fix this mutable nonsense.
    mutable uint32_t call_offset_;

  public:
    explicit ProcessorCallOpCode(void* location) : ProcessorCallOpCode(std::string(), location) { }

    // By default, call 'patch_call'
    // Todo: Determine if 'patch_call' should actually be here instead of under VCall.
    // Todo: Seems to make more sense I think.
    explicit ProcessorCallOpCode(std::string name) : ProcessorCallOpCode(name, nullptr) { }

    std::string rep() const;
    size_t size() const;
    void render(jit::JitRenderer&) const;

  private:
    ProcessorCallOpCode(std::string name, void* location):
      function_name_(name),
      static_location_((uintptr_t) &*location)
    {

    }

  private:
    void render_static_call(jit::JitRenderer& renderer) const;
    void render_call_stub(jit::JitRenderer& renderer) const;

    off_t determine_call_offset(uintptr_t current_location, uintptr_t to_location_) const {
      static off_t opcode_size = 5;
      return (to_location_ - (current_location + opcode_size));
    }
  };
}


#endif //__ProcessorCallOpCode_H_
