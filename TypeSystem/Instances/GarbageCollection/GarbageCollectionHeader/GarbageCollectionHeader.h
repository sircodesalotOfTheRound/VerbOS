//
// Created by Reuben Kuhnert on 14/9/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __GarbageCollectionHeader_H_
#define __GarbageCollectionHeader_H_

#include "TypeDef.h"
#import "GarbageCollectionFlags.h"

namespace types {
  class GarbageCollectionHeader {
    uint32_t offset_;
    uint16_t heap_number_;
    uint16_t flags_;

  public:
    uint32_t offset() const { return offset_; }
    uint16_t heap() const { return heap_number_; }

    bool is_visited() const { return (bool) (flags_ & GarbageCollectionFlags::VISITED); }
    bool is_sensitive() const { return (bool) (flags_ & GarbageCollectionFlags::SENSITIVE); }

    void set_visited(bool value) {
      if (value) {
        flags_ |= GarbageCollectionFlags::VISITED;
      } else {
        flags_ &= (uint16_t)~(GarbageCollectionFlags::VISITED);
      }
    }

  };
}


#endif //__GarbageCollectionHeader_H_
