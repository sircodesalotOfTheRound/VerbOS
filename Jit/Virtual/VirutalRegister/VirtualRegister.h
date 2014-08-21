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
        std::string name_;
        SystemType& type_;

    public:

        VirtualRegister(std::string name, SystemType& type) : name_(name), type_(type) { }

        std::string name() const { return name_; }
        SystemType&def() const { return type_; }

        friend std::ostream& operator<<(std::ostream& stream, const VirtualRegister& reg) {
            return stream << reg.name_ << " : " << reg.type_;
        }
    };
}


#endif //__VirtualRegister_H_
