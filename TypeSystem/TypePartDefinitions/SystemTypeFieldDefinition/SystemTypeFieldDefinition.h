//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef SYSTEM_TYPE_FIELD_DEFINITION
#define SYSTEM_TYPE_FIELD_DEFINITION

#include "TypeDef.h"
#include "TypeFamily.h"
#include "TypeFlags.h"
#include <string>

namespace types {
    class SystemType;
    class SystemTypeFieldDefinition {
        static const int default_size = sizeof(uintptr_t);

        std::string name_;
        const SystemType* type_;
        off_t offset_;
        TypeFlags flags_;

    public:
        SystemTypeFieldDefinition(std::string name, const SystemType& type, off_t offset, TypeFlags flags)
            : name_(name), type_(&type), offset_(offset), flags_(flags)
        {

        }

        std::string name() const { return name_; }
        off_t offset() { return offset_; }
        const SystemType& type() const { return *type_;}
        TypeFlags flags() { return flags_; }

    };
}


#endif //SYSTEM_TYPE_FIELD_DEFINITION
