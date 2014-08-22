
#ifndef OSX_REGISTERS_H
#define OSX_REGISTERS_H

#include <vector>
#include "CpuRegister.h"

namespace arch {
    class OsxRegisters {
    public:
        static const processor::CpuRegister rax;
        static const processor::CpuRegister rbx;
        static const processor::CpuRegister rcx;
        static const processor::CpuRegister rdx;

        static const processor::CpuRegister rsi;
        static const processor::CpuRegister rdi;

        static const processor::CpuRegister rbp;
        static const processor::CpuRegister rsp;


        static const processor::CpuRegister r8;
        static const processor::CpuRegister r9;
        static const processor::CpuRegister r10;
        static const processor::CpuRegister r11;
        static const processor::CpuRegister r12;
        static const processor::CpuRegister r13;
        static const processor::CpuRegister r14;
        static const processor::CpuRegister r15;


    private:
    };
}

#endif
