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
#include "TypeFamily.h"
#include "ContainerIterator.h"
#include "TypeFlags.h"
#include "InstanceClassPointer.h"

namespace types {
  class SystemType {
    std::string name_;
    std::unordered_map<std::string, SystemTypeFieldDefinition> field_definitions_;
    std::unordered_map<std::string, const SystemType*> trait_definitions_;

    off_t offset_;
    byte trait_count_;

    mutable size_t required_size_;
    TypeFamily family_;
    TypeFlags flags_;
    bool is_generic_;
    mutable bool is_frozen_;

  public:
    SystemType(std::string name, TypeFamily family, TypeFlags flags)
      : SystemType(name, family, flags, false) {

    }

    SystemType(std::string name, TypeFamily family, TypeFlags flags, bool is_generic)
      : name_(name),
        family_(family),
        flags_(flags),
        offset_(sizeof(Instance*)),
        trait_count_(0),
        is_generic_(is_generic),
        is_frozen_(false) {

    }

    void freeze() const;
    const SystemTypeFieldDefinition& field(std::string& name) const;
    bool is_frozen() const;
    void add_field_definition(const std::string name, const SystemType& type, TypeFlags flags);
    void add_trait(const SystemType& definition);
    bool isa(std::string name) const;
    bool isa(const SystemType& definition) const;
    off_t offset_by_name(std::string name);
    bool has_fields() const;
    size_t required_size() const;
    std::string name() const;
    size_t trait_count() const;
    size_t field_count() const;
    TypeFamily family() const;
    TypeFlags flags() const;
    helpers::ContainerIterator<decltype(trait_definitions_)> traits();
    helpers::ContainerIterator<decltype(field_definitions_)> fields();

    const static SystemType& NONE;

    friend std::ostream& operator<<(std::ostream& stream, const SystemType& type) {
      return stream << type.name_;
    }

  private:
    // Disable movement
    SystemType(const SystemType&) = delete;
    SystemType(SystemType&&) = delete;
    SystemType& operator=(const SystemType&) = delete;
    SystemType& operator=(SystemType&&) = delete;
  };
}


#endif //SYSTEM_TYPE
