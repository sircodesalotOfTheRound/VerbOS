//
// Created by Reuben Kuhnert on 14/8/25.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VerbajOpCodeBase.h"

#ifndef VSTAGE_ARG_H
#define VSTAGE_ARG_H

namespace verbaj {
  class VStageArg : public VerbajOpCodeBase {
    int variable_number;

  public:
    VStageArg(int virtual_register) : variable_number(virtual_register) {
    }

    void apply(jit::VirtualStackFrame&) const;
  };
}


#endif // VSTAGE_ARG_H
