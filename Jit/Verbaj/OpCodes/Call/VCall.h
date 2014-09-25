//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __VCall_H_
#define __VCall_H_

#include "VerbajOpCodeBase.h"

namespace verbaj {
  class VCall : public VerbajOpCodeBase {
    void* location_;

  public:
    template<class T>
    VCall(T location) : location_((void*) location) { }

    void apply(jit::VirtualStackFrame&) const;

    static VCall* load_op(std::istream& stream);
    static void patch_call();
    static void render(jit::JitRenderer &emitter);

  };
}


#endif //__VCall_H_
