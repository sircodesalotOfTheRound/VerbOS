//
// Created by Reuben Kuhnert on 14/10/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VerbajOpCodeBase.h"

#ifndef __VCopy_H_
#define __VCopy_H_

namespace verbaj {
  class VCopy : public VerbajOpCodeBase {
    int destination_;
    int source_;

  public:
    VCopy(int destination, int source);

    void apply(jit::Stackframe&) const override;
  };
}


#endif //__VCopy_H_
