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
#import "TypeFamily.h"
namespace types {
    class SystemType {
        std::string name_;
        std::unordered_map<std::string, SystemTypeFieldDefinition> field_definitions_;
        std::unordered_map<std::string, const SystemType*> trait_definitions_;

        byte field_count_;
        byte trait_count_;

        size_t required_size_;
        TypeFamily family_;
        bool is_frozen_;

    public:
        SystemType(std::string name, types::TypeFamily family)
            : name_(name),
            family_(family),
            field_count_(0),
            trait_count_(0),
            is_frozen_(false)
        {

        }

        void freeze() {
            // Todo: should ensure all dependent types (traits, subclasses, field types) are also
            // frozen (since the size of this type is dependent on the size of the others.
            is_frozen_ = true;
        }

        const SystemTypeFieldDefinition& field(std::string& name) const {
            return field_definitions_.at(name);
        }

        bool is_frozen() { return is_frozen_; }

        void add_field_definition(const std::string name, const SystemType& type) {
            if (is_frozen_) {
                throw std::logic_error("type is already frozen");
            }

            SystemTypeFieldDefinition definition { name, type, field_count_ };
            field_definitions_.insert({ definition.name(), definition });

            ++field_count_;
        }

        void add_trait(const SystemType& definition) {
            if (is_frozen_) {
                throw std::logic_error("type is already frozen");
            }

            if (definition.family_ != TypeFamily::CLASS || definition.family_ == TypeFamily::TRAIT) {
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

        size_t required_size() const { return required_size_; }

        std::string name() const { return name_; }
        size_t field_count() const { return field_definitions_.size(); }

        TypeFamily family() const { return family_; }

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
