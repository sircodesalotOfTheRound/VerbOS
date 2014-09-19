//
// Created by Reuben Kuhnert on 14/8/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __VerbajOpCodeSet_H_
#define __VerbajOpCodeSet_H_

#include <memory>
#include <vector>
#include "VerbajOpCodeBase.h"

namespace verbaj {
  class VerbajOpCodeSet {
    using iterator = std::vector<std::unique_ptr<VerbajOpCodeBase>>::iterator;

    std::vector<std::unique_ptr<VerbajOpCodeBase>> opcodes_;

  public:
    void add(VerbajOpCodeBase* op);

    iterator begin();

    iterator end();

  };
}


#endif //__VerbajOpCodeSet_H_
