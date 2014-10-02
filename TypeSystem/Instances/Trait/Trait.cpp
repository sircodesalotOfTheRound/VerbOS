//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "Trait.h"
#include "Instance.h"

const types::SystemType& types::Trait::def() const { return get_instance().type(); }

types::Instance& types::Trait::get_instance() const {
  return *instance_pointer_;
}

size_t types::Trait::get_member_offset(std::string& field_name) {
  return get_instance().member_offset(field_name);
}