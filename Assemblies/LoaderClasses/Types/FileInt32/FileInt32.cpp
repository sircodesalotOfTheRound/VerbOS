//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "FileInt32.h"

FileInt32::FileInt32(std::istream& stream) {
  stream.read((char*) &value_, sizeof(uint32_t));
}

uint32_t FileInt32::value() const {
  return value_;
}

FileInt32::operator uint32_t() const {
  return value_;
}