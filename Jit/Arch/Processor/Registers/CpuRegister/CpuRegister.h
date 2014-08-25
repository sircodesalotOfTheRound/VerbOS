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
                : name_(name), register_code_(code), size_(size), is_extended_(is_extended) {
        }

        const std::string &name() const;

        byte register_code() const;

        byte size() const;

        bool is_extended() const;

        bool operator==(const CpuRegister &rhs) const {
            return name_ == rhs.name_
                    && register_code_ == rhs.register_code_
                    && size_ == rhs.size_
                    && is_extended_ == rhs.is_extended_;
        }

        DereferencedCpuRegister operator*() const {
            return DereferencedCpuRegister(this);
        }

        DereferencedCpuRegister operator[](int offset) const {
            return DereferencedCpuRegister(this, offset);
        }

        friend std::ostream &operator<<(std::ostream &stream, const CpuRegister &cpu_register) {
            return stream << cpu_register.name_;
        }
    };

    // Defines
    using ConstCpuRegisterRef = const CpuRegister &;
}

// Hash for unordered maps
namespace std {
    template<>
    struct hash<arch::CpuRegister> {
        size_t operator()(const arch::CpuRegister &object) const {
            return (size_t)((object.register_code() * 11) + (object.size() * 13));
        }
    };
}



#endif //__CPURegister_H_
