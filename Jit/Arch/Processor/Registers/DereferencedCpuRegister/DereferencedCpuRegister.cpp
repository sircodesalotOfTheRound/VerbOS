//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "DereferencedCpuRegister.h"
#include "CpuRegister.h"

std::ostream& arch::operator<<(std::ostream& stream, const arch::DereferencedCpuRegister& reg) {
  return stream << "[" << reg.sys_register().name() << reg.offset() << "]";
}

arch::DereferencedCpuRegister arch::DereferencedCpuRegister::operator+(const int offset) {
  return DereferencedCpuRegister(sys_register_, this->offset_ + offset);
}

arch::DereferencedCpuRegister arch::DereferencedCpuRegister::operator-(const int offset) {
  return DereferencedCpuRegister(sys_register_, this->offset_ - offset);
}

const arch::CpuRegister& arch::DereferencedCpuRegister::sys_register() const {
  return *sys_register_;
}

off_t arch::DereferencedCpuRegister::offset() const {
  return offset_;
}