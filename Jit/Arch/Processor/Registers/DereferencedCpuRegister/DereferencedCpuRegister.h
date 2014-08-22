//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __DereferencedCpuRegister_H_
#define __DereferencedCpuRegister_H_

#include <iostream>
#include <memory>

namespace arch {
    class CpuRegister;
    class DereferencedCpuRegister {
        const CpuRegister *sys_register_;
        off_t offset_;

    public:
        DereferencedCpuRegister(const CpuRegister *reg, off_t offset) :
                sys_register_(reg),
                offset_(offset) {
        }

        DereferencedCpuRegister(const CpuRegister *reg) : DereferencedCpuRegister(reg, 0) {

        }

        DereferencedCpuRegister operator+=(const int offset) {
            return DereferencedCpuRegister(sys_register_, this->offset_ + offset);
        }

        DereferencedCpuRegister operator-=(const int offset) {
            return DereferencedCpuRegister(sys_register_, this->offset_ - offset);
        }

        const CpuRegister &sys_register() const {
            return *sys_register_;
        };

        off_t offset() const {
            return offset_;
        }
    };

    std::ostream& operator<<(std::ostream& stream, const arch::DereferencedCpuRegister& sys_register);
}


#endif //__DereferencedCpuRegister_H_
