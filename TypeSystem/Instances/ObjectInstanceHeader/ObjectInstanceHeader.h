//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ObjectInstanceHeader_H_
#define __ObjectInstanceHeader_H_

#include "TypeDef.h"
#include "SystemType.h"

namespace types {
    struct ObjectInstanceHeader {
        // 0 - 8 : System Type
        // 9 - 16 : Garbage Collection Meta
        using raw_header_bytes = uintptr_t[2];
        raw_header_bytes data_;

        SystemType& type() { return *(SystemType*)(data_[0]); }
    };
}


#endif //__ObjectInstanceHeader_H_
