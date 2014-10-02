//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __VLdui64_H_
#define __VLdui64_H_

#include "VerbajOpCodeBase.h"

namespace verbaj {
  class VLdui64 : public VerbajOpCodeBase {
    int register_index;
    uint64_t value_;

  public:
    VLdui64(int to_register, uint64_t value) : register_index(to_register), value_(value) { }

    void apply(jit::Stackframe& frame) const override;

    static VerbajOpCodeBase* load_op(std::istream& stream);

  private:
    void perform_load(jit::VariableCheckout&) const;
  };
}


#endif //__Ldui64_H_
