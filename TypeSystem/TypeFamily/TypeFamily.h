//
// Created by Reuben Kuhnert on 14/9/4.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __TypeFamily_H_
#define __TypeFamily_H_

namespace types {
    enum class TypeFamily {
        PRIMITIVE,
        CLASS,
        ABSTRACT_CLASS,
        TRAIT,
        FUNCTION
    };
}


#endif //__TypeFamily_H_
