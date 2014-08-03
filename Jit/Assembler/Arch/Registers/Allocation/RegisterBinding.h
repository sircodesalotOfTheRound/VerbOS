//
// Created by Reuben Kuhnert on 14/8/2.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __RegisterBinding_H_
#define __RegisterBinding_H_

#include <iostream>
#include "SystemRegister.h"

namespace hla {
    class Variable;
}

namespace sysarch {
    class RegisterBinding {
        int priority_ { 0 };
        hla::Variable* variable_;
        SystemRegister* register_;

    public:
        RegisterBinding(SystemRegister& reg) : register_(&reg), variable_(nullptr) { }
        hla::Variable& variable();

        void variable(hla::Variable& variable);

        bool operator<(const RegisterBinding& rhs) const { return rhs.priority_ < priority_; }

        const SystemRegister& sys_register() const { return *register_; }

        bool has_variable() { return variable_ != nullptr; }
        int priority() { return priority_; }

        friend std::ostream& operator<<(std::ostream& stream, const RegisterBinding& binding);
    };
}

#endif //__RegisterBinding_H_
