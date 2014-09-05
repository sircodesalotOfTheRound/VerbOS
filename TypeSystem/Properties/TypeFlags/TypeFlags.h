//
// Created by Reuben Kuhnert on 14/9/4.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __TypeFlags_H_
#define __TypeFlags_H_

namespace types {
    enum class TypeFlags {
        PUBLIC = 1,
        PRIVATE = 2,
        PROTECTED = 4,
        INTERNAL = 8,

        STATIC = 16,
    };
}


#endif //__TypeFlags_H_
