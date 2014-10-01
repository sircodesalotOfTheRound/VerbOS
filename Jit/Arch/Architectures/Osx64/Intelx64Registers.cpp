#include "CpuRegister.h"
#include "Intelx64Registers.h"


const arch::CpuRegister arch::Intelx64Registers::rax{"rax", 0x00, 64, false};
const arch::CpuRegister arch::Intelx64Registers::rbx{"rbx", 0x03, 64, false};
const arch::CpuRegister arch::Intelx64Registers::rcx{"rcx", 0x01, 64, false};
const arch::CpuRegister arch::Intelx64Registers::rdx{"rdx", 0x02, 64, false};

const arch::CpuRegister arch::Intelx64Registers::rsi{"rsi", 0x06, 64, false};
const arch::CpuRegister arch::Intelx64Registers::rdi{"rdi", 0x07, 64, false};

const arch::CpuRegister arch::Intelx64Registers::rsp{"rsp", 0x04, 64, false};
const arch::CpuRegister arch::Intelx64Registers::rbp{"rbp", 0x05, 64, false};

const arch::CpuRegister arch::Intelx64Registers::r8{"r8", 0x00, 64, true};
const arch::CpuRegister arch::Intelx64Registers::r9{"r9", 0x01, 64, true};
const arch::CpuRegister arch::Intelx64Registers::r10{"r10", 0x02, 64, true};
const arch::CpuRegister arch::Intelx64Registers::r11{"r11", 0x03, 64, true};
const arch::CpuRegister arch::Intelx64Registers::r12{"r12", 0x04, 64, true};
const arch::CpuRegister arch::Intelx64Registers::r13{"r13", 0x05, 64, true};
const arch::CpuRegister arch::Intelx64Registers::r14{"r14", 0x06, 64, true};
const arch::CpuRegister arch::Intelx64Registers::r15{"r15", 0x07, 64, true};

