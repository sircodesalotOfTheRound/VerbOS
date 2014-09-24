//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "FileInt8.h"

FileInt8::FileInt8(std::istream& stream) {
  stream.read((char*) &value_, sizeof(uint8_t));
}

uint8_t FileInt8::value() const {
  return value_;
}

FileInt8::operator uint8_t() const {
  return value_;
}