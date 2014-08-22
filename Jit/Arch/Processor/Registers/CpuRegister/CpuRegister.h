//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef CPU_REGISTER_H
#define CPU_REGISTER_H

#include <string>
#include "DereferencedCpuRegister.h"
#include "TypeDef.h"

namespace arch {
    class CpuRegister {
        std::string name_;
        byte register_code_;
        byte size_;
        bool is_extended_;

    public:
        CpuRegister(std::string name, byte code, byte size, bool is_extended)
            : name_(name), register_code_(code), size_(size), is_extended_(is_extended) { }

        const std::string& name() const;
        byte register_code() const;
        byte size() const;
        bool is_extended() const;

        DereferencedCpuRegister operator*() const { return DereferencedCpuRegister(this); }
        DereferencedCpuRegister operator[](int offset) const { return DereferencedCpuRegister(this, offset); }

        friend std::ostream& operator<<(std::ostream& stream, const CpuRegister & cpu_register) {
            return stream << cpu_register.name_;
        }
    };
}


#endif //__CPURegister_H_
