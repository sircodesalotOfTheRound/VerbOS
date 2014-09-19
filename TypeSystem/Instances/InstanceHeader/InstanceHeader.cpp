//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "InstanceHeader.h"

types::GarbageCollectionHeader& types::InstanceHeader::gc_header() {
  return gc_header_;
}

const types::SystemType& types::InstanceHeader::type() const {
  return *type_;
}