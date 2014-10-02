//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "Stackframe.h"
#include "VerbajOpCodeBase.h"

#ifndef __VRet_H_
#define __VRet_H_


namespace verbaj {
  class VRet : public VerbajOpCodeBase {
    int register_index_;

  public:
    VRet(int register_index) : register_index_(register_index) { }

    void apply(jit::Stackframe&) const override;

    static VRet* load_op(std::istream& stream);
  };
}


#endif //__VRet_H_
