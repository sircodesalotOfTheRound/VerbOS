//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "CpuRegister.h"

bool arch::CpuRegister::is_extended() const {
  return is_extended_;
}

byte arch::CpuRegister::size() const {
  return size_;
}

byte arch::CpuRegister::register_code() const {
  return register_code_;
}

const std::string& arch::CpuRegister::name() const {
  return name_;
}

bool arch::CpuRegister::operator==(const CpuRegister& rhs) const {
  return name_ == rhs.name_
    && register_code_ == rhs.register_code_
    && size_ == rhs.size_
    && is_extended_ == rhs.is_extended_;
}

bool arch::CpuRegister::operator!=(const CpuRegister& rhs) const {
  return !(*this == rhs);
}

arch::DereferencedCpuRegister arch::CpuRegister::operator*() const {
  return DereferencedCpuRegister(this);
}

arch::DereferencedCpuRegister arch::CpuRegister::operator[](int offset) const {
  return DereferencedCpuRegister(this, offset);
}