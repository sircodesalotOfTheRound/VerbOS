//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <string>

#ifndef __FieldDefinition_H_
#define __FieldDefinition_H_

namespace typesys {
    enum class FIELD_FLAGS {
        PUBLIC,
        PRIVATE,
        PROTECTED
    };

    class FieldDefinition {
        FIELD_FLAGS flags;
        std::string name_;

    public:

        std::string name() { return name_; }
    };
}


#endif //__FieldDefinition_H_
