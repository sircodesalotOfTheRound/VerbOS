//
// Created by Reuben Kuhnert on 14/9/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VerbajOpCodeBase.h"
#include "Trait.h"

#ifndef __Ldutf8_H_
#define __Ldutf8_H_

namespace verbaj {
  class VLdutf8 : public VerbajOpCodeBase {
    int variable_number_;
    std::string string_;

  public:
    VLdutf8(int virtual_variable_index, std::string string)
      : variable_number_(virtual_variable_index),
      string_(string)
    {

    }

    void apply(jit::VirtualStackFrame&) const;
  };
}

#endif //__Ldutf8_H_
