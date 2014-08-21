//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <string>
#include "CpuRegister.h"
#include "SystemType.h"

#ifndef __VirtualRegister_H_
#define __VirtualRegister_H_

namespace jit {
    class VirtualRegister {
        using SystemWord = uint64_t;

        const std::string name_;
        const SystemType& type_;

        SystemWord value_;

    public:

        VirtualRegister(std::string name, const SystemType& type) : name_(name), type_(type) { }

        std::string name() const { return name_; }
        SystemWord value() const { return value_; }
        const SystemType &def() const { return type_; }

        friend std::ostream& operator<<(std::ostream& stream, const VirtualRegister& reg) {
            return stream << reg.name_ << " : " << reg.type_;
        }

        const static VirtualRegister& EMPTY;
    };
}


#endif //__VirtualRegister_H_
