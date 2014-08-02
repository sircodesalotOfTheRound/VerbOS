//
// Created by Reuben Kuhnert on 14/8/2.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "SystemRegister.h"

namespace sysarch {
    DereferencedRegister SystemRegister::operator[](int index) const {
        return DereferencedRegister(*this, index);
    }

    DereferencedRegister SystemRegister::operator*() const {
        return DereferencedRegister(*this, 0);
    }
}
