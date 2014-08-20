//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "CpuRegister.h"

bool processor::CpuRegister::is_extended() const { return is_extended_; }
byte processor::CpuRegister::size() const { return size_; }
byte processor::CpuRegister::register_code() const { return register_code_; }
const std::string &processor::CpuRegister::name() const { return name_; }