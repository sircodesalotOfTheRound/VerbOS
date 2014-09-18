#ifndef OSX_REGISTERS_H
#define OSX_REGISTERS_H

#include <vector>
#include "CpuRegister.h"

namespace arch {
  struct OsxRegisters {
    static const arch::CpuRegister rax;
    static const arch::CpuRegister rbx;
    static const arch::CpuRegister rcx;
    static const arch::CpuRegister rdx;

    static const arch::CpuRegister rsi;
    static const arch::CpuRegister rdi;

    static const arch::CpuRegister rbp;
    static const arch::CpuRegister rsp;


    static const arch::CpuRegister r8;
    static const arch::CpuRegister r9;
    static const arch::CpuRegister r10;
    static const arch::CpuRegister r11;
    static const arch::CpuRegister r12;
    static const arch::CpuRegister r13;
    static const arch::CpuRegister r14;
    static const arch::CpuRegister r15;
  };
}

#endif
