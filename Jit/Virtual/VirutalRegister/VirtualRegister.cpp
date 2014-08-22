//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VirtualRegister.h"


const jit::VirtualRegister& jit::VirtualRegister::EMPTY = jit::VirtualRegister("<EMPTY>", SystemType::NONE, -1);