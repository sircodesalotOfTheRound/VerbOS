//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "CpuRegister.h"

bool arch::CpuRegister::is_extended() const { return is_extended_; }
byte arch::CpuRegister::size() const { return size_; }
byte arch::CpuRegister::register_code() const { return register_code_; }
const std::string &arch::CpuRegister::name() const { return name_; }