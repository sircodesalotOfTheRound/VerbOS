//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "CPURegister.h"

bool processor::CPURegister::is_extended() const { return is_extended_; }
byte processor::CPURegister::size() const { return size_; }
byte processor::CPURegister::register_code() const { return register_code_; }
const std::string &processor::CPURegister::name() const { return name_; }