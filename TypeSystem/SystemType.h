//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef SYSTEM_TYPE
#define SYSTEM_TYPE

#include <string>
#include <array>
#include <vector>
#include <algorithm>

#include "TypeDef.h"
#include "SystemTypeFieldDefinition.h"

class SystemType {
    std::string name_;
    std::vector<SystemTypeFieldDefinition> field_definitions_;

public:
    SystemType(std::string name, byte field_count)
        : name_(name)
    {
        field_definitions_.reserve(field_count);
    }

    SystemType(const SystemType&) = delete;
    SystemType(SystemType&&) = delete;
    SystemType& operator=(const SystemType&) = delete;
    SystemType& operator=(SystemType&&) = delete;

    void add_field_definition(const SystemTypeFieldDefinition definition) {
        if (field_definitions_.size() >= field_definitions_.capacity()) {
            throw std::logic_error("more fields added than specified");
        }

        field_definitions_.push_back(definition);
    }

    size_t field_count() const { return field_definitions_.size(); }

private:
    friend std::ostream& operator<<(std::ostream& stream, const SystemType& type) {
        return stream << type.name_;
    }
};


#endif //SYSTEM_TYPE
