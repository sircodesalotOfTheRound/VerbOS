//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "DereferencedCpuRegister.h"
#include "CpuRegister.h"

std::ostream&arch::operator<<(std::ostream& stream, const arch::DereferencedCpuRegister& reg) {
    return stream << "[ " << reg.sys_register().name() << reg.offset() << "]";
}
