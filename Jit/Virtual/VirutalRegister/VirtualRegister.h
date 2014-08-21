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

        int priority_;
        std::string name_;
        mutable const SystemType* type_;

        SystemWord value_;

    public:
        VirtualRegister() : VirtualRegister(VirtualRegister::EMPTY) { }

        VirtualRegister(std::string name, const SystemType& type, int priority)
            : name_(name),
              type_(&type),
              priority_(priority)
        {

        }

        VirtualRegister(const VirtualRegister& rhs)
            : name_(rhs.name_),
              type_(rhs.type_),
              priority_(rhs.priority_)
        {

        }

        VirtualRegister& operator=(const VirtualRegister& rhs) {
            if (this == &rhs) return *this;

            name_ = rhs.name_;
            type_ = rhs.type_;
            priority_ = rhs.priority_;

            return *this;
        }

        std::string name() const { return name_; }
        SystemWord value() const { return value_; }
        int priority() const { return priority_; }

        const SystemType &def() const { return *type_; }

        friend std::ostream& operator<<(std::ostream& stream, const VirtualRegister& reg) {
            return stream << reg.name_ << " : " << *reg.type_;
        }

        const static VirtualRegister& EMPTY;
    };
}


#endif //__VirtualRegister_H_
