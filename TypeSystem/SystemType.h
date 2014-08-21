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
#include <unordered_map>
#include <iostream>

#include "TypeDef.h"
#include "SystemTypeFieldDefinition.h"

class SystemType {
    std::string name_;
    std::unordered_map<std::string, SystemTypeFieldDefinition> field_definitions_;
    std::unordered_map<std::string, SystemType*> trait_definitions_;
    byte field_offset_ { 0 };
    byte trait_offset_ { 0 };

public:
    SystemType(std::string name, byte field_count, byte trait_count)
        : name_(name)
    {
        field_definitions_.reserve(field_count);
        field_definitions_.reserve(trait_count);
    }

    SystemType(const SystemType&) = delete;
    SystemType(SystemType&&) = delete;
    SystemType& operator=(const SystemType&) = delete;
    SystemType& operator=(SystemType&&) = delete;

    void add_field_definition(const std::string name, const SystemType& type) {
        SystemTypeFieldDefinition definition { name, type, field_offset_++ };
        field_definitions_.insert({ definition.name(), definition });
    }

    void add_trait(SystemType& definition) {
        trait_definitions_.insert({ definition.name(), &definition });
    }

    bool isa(std::string name) const {
        if (name_ == name) return true;
        if (trait_definitions_.find(name) != trait_definitions_.end()) return true;

        for (auto entry : trait_definitions_) {
            if (entry.second->isa(name)) return true;
        }

        return false;
    }

    std::string name() const { return name_; }
    size_t field_count() const { return field_definitions_.size(); }

    const static SystemType& NONE;

private:
    friend std::ostream& operator<<(std::ostream& stream, const SystemType& type) {
        return stream << type.name_;
    }
};


#endif //SYSTEM_TYPE
