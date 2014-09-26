//
// Created by Reuben Kuhnert on 14/9/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "FunctionTable.h"

std::unordered_map<std::string, void*> env::FunctionTable::entries_ { };
std::unordered_map<uintptr_t, std::string> env::FunctionTable::call_stubs_ { };
