//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "InstanceClassPointer.h"

types::Instance& types::InstanceClassPointer::operator*() const {
  return *self_;
}

types::Instance* types::InstanceClassPointer::operator->() const {
  return self_;
}