#include "CPURegister.h"

#ifndef OSX_REGISTERS_H
#define OSX_REGISTERS_H

namespace arch {
    class OsxRegisters {
    public:
        static const processor::CPURegister rax;
        static const processor::CPURegister rbx;
        static const processor::CPURegister rcx;
        static const processor::CPURegister rdx;

        static const processor::CPURegister rsi;
        static const processor::CPURegister rdi;

        static const processor::CPURegister rbp;
        static const processor::CPURegister rsp;


        static const processor::CPURegister r8;
        static const processor::CPURegister r9;
        static const processor::CPURegister r10;
        static const processor::CPURegister r11;
        static const processor::CPURegister r12;
        static const processor::CPURegister r13;
        static const processor::CPURegister r14;
        static const processor::CPURegister r15;


    };
}

#endif
