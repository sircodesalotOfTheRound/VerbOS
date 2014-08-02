//
// Created by Reuben Kuhnert on 14/8/2.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __SystemRegister_H_
#define __SystemRegister_H_

#include <string>
#include <iostream>
#include "DereferencedRegister.h"

namespace sysarch {

    class SystemRegister {
        std::string name_;
        uint8_t reg_code_;
        size_t reg_size_;
        bool is_extended_;

    public:
        SystemRegister(std::string name,
                uint8_t reg_code,
                size_t reg_size,
                bool is_extended)
                : name_(name),
                  reg_code_(reg_code),
                  reg_size_(reg_size),
                  is_extended_(is_extended) {

        }

        std::string name() const { return name_; }
        uint8_t register_code() const { return reg_code_; }
        size_t register_size() const { return reg_size_; }
        bool is_extended() const { return is_extended_; }

        DereferencedRegister operator*() const;
        DereferencedRegister operator[](int index) const;

        friend std::ostream &operator<<(std::ostream &stream, const SystemRegister &sys_register) {
            return stream << sys_register.name();
        }
    };

    using p_sys_register = const SystemRegister * const;
}


#endif //__SystemRegister_H_
