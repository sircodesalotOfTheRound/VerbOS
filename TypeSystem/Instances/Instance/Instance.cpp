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
  // TODO: Fix this.
  size_t total_required_size = 256;//type.required_size() + sizeof(InstanceHeader);
  std::cout << "allocating:" << total_required_size << std::endl;
  return new(total_required_size) Instance(type);
}

void* types::Instance::operator new(size_t size, size_t required_size) {
  // Todo: Instances should use their own allocator, since they are only created (never destroyed)
  // except when all types in the environment are destroyed as well. Thus we can save memory
  // by creating a 'write once' allocator.
  return malloc(required_size);
}

types::Trait* types::Instance::head() { return &head_trait_; }