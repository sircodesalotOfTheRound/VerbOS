//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VerbosType_H_
#define __VerbosType_H_

#include <string>
#include "VMString.h"

namespace typesys {
    enum class TYPE_FLAGS : uint64_t {
        COMPLETE_DEFINITION = 0x01,
        CLASS = 0x02,
        TRAIT = 0x04,
        ABSTRACT = 0x08,
        INJECTED = 0x10,
        STATIC = 0x20,
        SENSITIVE = 0x40,
        SERVICE = 0x80,
        OPTION = 0x100,
        PROXY = 0x200,

        BLOCKING_FUNCTION = 0x400,
        ASYNC_FUNCTION = 0x800,
        YIELD_FUNCTION = 0x1000,
        SERVICE_FUNCTION = 0x2000,

        SQL = 0x4000,
        META = 0x8000,
        ENVIRONMENT = 0x10000,
        NATIVE = 0x2000,

        PUBLIC = 0x40000,
        PRIVATE = 0x80000,
        PROTECTED = 0x100000,
        INTERNAL = 0x200000,
    };


    class VerbosType {
        TYPE_FLAGS flags;
        vm::VMString name_;

    public:
        VerbosType(std::string name) : name_(name) { }

        std::string name() const { return name_.str(); }

        friend std::ostream& operator<<(std::ostream& stream, const VerbosType& type) {
            return stream << type.name();
        }
    };
}


#endif //__VerbosType_H_
