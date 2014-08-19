//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef SYSTEM_TYPE_FIELD_DEFINITION
#define SYSTEM_TYPE_FIELD_DEFINITION

#include "TypeDef.h"
#include <string>

class SystemType;
class SystemTypeFieldDefinition {
    std::string name_;
    const SystemType* type_;

public:
    SystemTypeFieldDefinition(std::string name, const SystemType& type)
        : name_(name), type_(&type) {

    }

    std::string name() const { return name_; }
    const SystemType& type() const { return *type_;}

};


#endif //SYSTEM_TYPE_FIELD_DEFINITION
