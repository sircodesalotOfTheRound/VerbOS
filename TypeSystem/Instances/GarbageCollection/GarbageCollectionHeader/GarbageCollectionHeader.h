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
        GarbageCollectionFlags flags;


    };
}


#endif //__GarbageCollectionHeader_H_
