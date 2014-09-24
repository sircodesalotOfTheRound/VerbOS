//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "FileString.h"

std::string FileString::text() const { return text_; }

FileString::operator std::string() const {
  return text_;
}
