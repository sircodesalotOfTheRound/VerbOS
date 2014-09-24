//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "FileInt64.h"

FileInt64::FileInt64(std::istream& stream) {
  stream.read((char*) &value_, sizeof(uint64_t));
}

uint64_t FileInt64::value() const {
  return value_;
}

FileInt64::operator uint64_t() const {
  return value_;
}