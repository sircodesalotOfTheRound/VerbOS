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
  };
}


#endif //__VCall_H_
