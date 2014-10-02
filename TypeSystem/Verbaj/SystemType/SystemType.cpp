//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "SystemType.h"
#include "Trait.h"
#include "Instance.h"

const types::SystemType& types::SystemType::NONE = SystemType("<NONE>", types::TypeFamily::PRIMITIVE, types::TypeFlags::PUBLIC);


types::SystemType::SystemType(std::string name, TypeFamily family, TypeFlags flags, bool is_generic) : name_(name),
    family_(family),
    flags_(flags),
    offset_(0),
    trait_count_(0),
    is_generic_(is_generic),
    is_frozen_(false)
{

}


void types::SystemType::freeze() const {
  // If the type is already frozen, return.
  if (is_frozen()) {
    return;
  }

  // Todo: should ensure all dependent types (traits, subclasses, field types) are also
  // frozen (since the size of this type is dependent on the size of the others.
  is_frozen_ = true;

  // Todo: correct this calculation;
  size_t size_required_for_traits = 0;

  for (auto trait_iter : trait_definitions_) {
    auto& trait = trait_iter.second;

    // First freeze the trait.
    trait->freeze();

    // Only add a trait band if the trait has specific data associated with it.
    if (trait->has_fields()) {
      // Add the size of the trait (the 'self' pointer)
      size_required_for_traits += trait->required_size() + sizeof(Trait);
    }
  }

  size_t total_size_required = (size_t)(offset_ + size_required_for_traits);

  // If this contains fields, then we need to add the size of a self-pointer.
  if (offset_ > 0) {
    required_size_ = total_size_required + sizeof(Instance*);
  } else {
    required_size_ = total_size_required;
  }
}

const types::SystemTypeFieldDefinition& types::SystemType::field(std::string& name) const {
  if (field_definitions_.find(name) == field_definitions_.end()) {
    throw std::logic_error("no such field found");
  }

  return field_definitions_.at(name);
}

bool types::SystemType::is_frozen() const {
  return is_frozen_;
}

void types::SystemType::add_field_definition(const std::string name, const SystemType& type, TypeFlags flags) {
  if (is_frozen_) {
    throw std::logic_error("type is already frozen");
  }

  SystemTypeFieldDefinition definition{name, type, offset_, flags};
  field_definitions_.insert({definition.name(), definition});

  offset_ += 8;
}

void types::SystemType::add_trait(const SystemType& definition) {
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

  trait_definitions_.insert({definition.name(), &definition});

  ++trait_count_;
}

bool types::SystemType::isa(std::string name) const {
  if (name_ == name) return true;
  if (trait_definitions_.find(name) != trait_definitions_.end()) return true;

  for (auto entry : trait_definitions_) {
    if (entry.second->isa(name)) return true;
  }

  return false;
}

bool types::SystemType::isa(const SystemType& type) const {
  return isa(type.name_);
}

off_t types::SystemType::offset_by_name(std::string name) {
  return field_definitions_.at(name).offset();
}

bool types::SystemType::has_fields() const {
  return offset_ > 0;
}

size_t types::SystemType::required_size() const {
  return required_size_;
}

std::string types::SystemType::name() const {
  return name_;
}

size_t types::SystemType::trait_count() const {
  return trait_definitions_.size();
}

size_t types::SystemType::field_count() const {
  return field_definitions_.size();
}

types::TypeFamily types::SystemType::family() const {
  return family_;
}

types::TypeFlags types::SystemType::flags() const {
  return flags_;
}

helpers::ContainerIterator<decltype(types::SystemType::trait_definitions_)> types::SystemType::traits() {
  return trait_definitions_;
}

helpers::ContainerIterator<decltype(types::SystemType::field_definitions_)> types::SystemType::fields() {
  return field_definitions_;
}

