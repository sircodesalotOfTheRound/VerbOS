//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "Instance.h"

const types::SystemType& types::Instance::type() const {
  return header_.type();
}

void* types::Instance::operator new(size_t size, const SystemType& type) {
  // Initialize the memory after creating it.
  // Since we have everything we need to build the
  // type right here. Then return and allow default (empty)
  // constructor to run.

  // Todo: This line is mostly correct, but doesn't work for arrays or strings.
  // return new(type.required_size() + sizeof(Instance)) Instance(type);

  return new(256) Instance (type);
}

void* types::Instance::operator new(size_t size, size_t required_size) {
  // Todo: Instances should use their own allocator, since they are only created (never destroyed)
  // except when all types in the environment are destroyed as well. Thus we can save memory
  // by creating a 'write once' allocator.
  return malloc(required_size);
}

types::Trait* types::Instance::head() { return &head_trait_; }

size_t types::Instance::member_offset(std::string name) const {
  const SystemType& type = this->type();
  const SystemTypeFieldDefinition& field = type.field(name);

  return (size_t) field.offset();
}
