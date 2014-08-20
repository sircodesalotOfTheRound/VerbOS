//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "DereferencedCpuRegister.h"
#include "CpuRegister.h"

std::ostream& processor::operator<<(std::ostream& stream, const processor::DereferencedCpuRegister& reg) {
    return stream << reg.sys_register().name() << " [" << reg.offset() << "] ";
}
