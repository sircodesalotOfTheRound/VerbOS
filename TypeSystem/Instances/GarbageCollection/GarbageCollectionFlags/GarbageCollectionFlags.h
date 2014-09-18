//
// Created by Reuben Kuhnert on 14/9/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __GarbageCollectionFlags_H_
#define __GarbageCollectionFlags_H_

#include "TypeDef.h"
#include "Functions.h"

namespace types {
  enum class GarbageCollectionFlags : uint16_t {
    VISITED = 0x01,
    SENSITIVE = 0x02
  };
}

#endif //__GarbageCollectionFlags_H_
