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

namespace types {
    class SystemType {
        std::string name_;
        std::unordered_map<std::string, SystemTypeFieldDefinition> field_definitions_;
        std::unordered_map<std::string, const SystemType*> trait_definitions_;

        byte field_count_;
        byte trait_count_;

        mutable size_t required_size_;
        TypeFamily family_;
        TypeFlags flags_;
        bool is_generic_;
        mutable bool is_frozen_;

    public:
        SystemType(std::string name, TypeFamily family, TypeFlags flags)
            : SystemType(name, family, flags, false)
        {

        }

        SystemType(std::string name, TypeFamily family, TypeFlags flags, bool is_generic)
            : name_(name),
            family_(family),
            flags_(flags),
            field_count_(0),
            trait_count_(0),
            is_generic_(is_generic),
            is_frozen_(false)
        {

        }

        void freeze() const;

        const SystemTypeFieldDefinition& field(std::string& name) const {
            return field_definitions_.at(name);
        }

        bool is_frozen() const { return is_frozen_; }

        void add_field_definition(const std::string name, const SystemType& type, TypeFlags flags) {
            if (is_frozen_) {
                throw std::logic_error("type is already frozen");
            }

            SystemTypeFieldDefinition definition { name, type, field_count_, flags};
            field_definitions_.insert({ definition.name(), definition });

            ++field_count_;
        }

        void add_trait(const SystemType& definition) {
            if (is_frozen_) {
                throw std::logic_error("type is already frozen");
            }

            if (definition.family_ != TypeFamily::CLASS
                && definition.family_ != TypeFamily::ABSTRACT_CLASS
                && definition.family_ != TypeFamily::TRAIT) {

                throw std::logic_error("traits must be either 'traits' or classes'");
            }

            // Base classes must be added first.
            if (definition.family_ == TypeFamily::CLASS && trait_count_ > 0) {
                throw std::logic_error("A type can have only one base class, and it must be added first");
            }

            trait_definitions_.insert({ definition.name(), &definition });

            ++trait_count_;
        }

        bool isa(std::string name) const {
            if (name_ == name) return true;
            if (trait_definitions_.find(name) != trait_definitions_.end()) return true;

            for (auto entry : trait_definitions_) {
                if (entry.second->isa(name)) return true;
            }

            return false;
        }

        bool has_fields() const { return field_count_ > 0; }
        size_t required_size() const { return required_size_; }

        std::string name() const { return name_; }

        size_t trait_count() const { return trait_definitions_.size(); }
        size_t field_count() const { return field_definitions_.size(); }

        TypeFamily family() const { return family_; }
        TypeFlags flags() const { return flags_; }

        helpers::ContainerIterator<decltype(trait_definitions_)> traits() { return trait_definitions_; }
        helpers::ContainerIterator<decltype(field_definitions_)> fields() { return field_definitions_; }

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
