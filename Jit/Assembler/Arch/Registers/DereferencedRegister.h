
#ifndef REGISTER_WITH_OFFSET_H
#define REGISTER_WITH_OFFSET_H

#include "Types.h"

// Represents a dereferencing action:
// For example:
// lea rax, variable       ; Load the address of 'variable'.
// mov rax, [rax]          ; Dereference [rax] and move to rax.
//
// This class represents dereferencing a register such as [rax] (as opposed to 'rax').

namespace sysarch {

    class SystemRegister;
    typedef const SystemRegister& const_sys_register;

    class DereferencedRegister {
        const_sys_register sys_register_;
        off_t offset_;

    public:
        DereferencedRegister(const_sys_register sys_register) :
            sys_register_(sys_register), offset_(0)
        {

        }

        DereferencedRegister(const_sys_register sys_register, off_t offset)
            : sys_register_(sys_register),
            offset_(offset)
        {

        }

        DereferencedRegister operator+(off_t rhs) {
            return DereferencedRegister(sys_register_, offset_ + rhs);
        }

        DereferencedRegister operator-(off_t rhs) {
            return DereferencedRegister(sys_register_, offset_ - rhs);
        }

        bool has_offset() { return offset_ != 0; }
        const_sys_register sys_register() { return sys_register_; }
        off_t offset() { return offset_; }
    };
}

#endif
