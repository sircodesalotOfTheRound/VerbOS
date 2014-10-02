//
// Created by Reuben Kuhnert on 14/9/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __Ldutf8_H_
#define __Ldutf8_H_

#include "VerbajOpCodeBase.h"
#include "Trait.h"
#include "FileInt8.h"
#include "FileString.h"
#include <iostream>

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

    void apply(jit::Stackframe&) const override;

    static VLdutf8* load_op(std::istream& stream) {
      FileInt8 variable_number(stream);
      FileString text(stream);

      return new VLdutf8(variable_number, text);
    }
  };
}

#endif //__Ldutf8_H_
