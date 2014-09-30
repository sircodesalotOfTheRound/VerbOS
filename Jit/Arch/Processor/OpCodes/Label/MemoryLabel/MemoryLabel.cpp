//
// Created by Reuben Kuhnert on 14/9/30.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "MemoryLabel.h"

op::MemoryLabel::MemoryLabel(std::string name, void* memory_location):
  name_(name), memory_location_(memory_location)
{

}

op::MemoryLabel::MemoryLabel(std::string name):
  name_(name), memory_location_(nullptr)
{

}

void op::MemoryLabel::set_location(void* memory_location) {
  if (this->memory_location_) {
    throw std::logic_error("label already has an address");
  }

  // Set the memory location
  memory_location_ = memory_location;

  // Now that the location is set, perform the callbacks.
  callbacks_.update(memory_location);
  callbacks_.clear();
}

bool op::MemoryLabel::is_location_fixed() const {
  return memory_location_ != nullptr;
}

std::string op::MemoryLabel::name() const {
  return name_;
}

void op::MemoryLabel::add_callback(std::function<void(void*)> callback) {
  // If the address is already fixed, then just run the callback.
  if (is_location_fixed()) {
    callback(memory_location_);
  } else {
    callbacks_.add(callback);
  }
}
