//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __VCall_H_
#define __VCall_H_

#include "VerbajOpCodeBase.h"
#include "Stackframe.h"

namespace verbaj {
  class VCall : public VerbajOpCodeBase {
    void* location_;
    std::string name_;

  public:
    VCall(void* location) : location_(location) { }
    VCall(std::string name) : name_(name) { }

    void apply(jit::Stackframe&) const override;

    static VCall* load_op(std::istream& stream);

    static void patch_call();
    static void render(jit::JitRenderer &emitter);

  };
}


#endif //__VCall_H_
