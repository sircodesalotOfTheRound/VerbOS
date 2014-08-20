#include "CPURegister.h"
#include "OsxRegisters.h"

const processor::CPURegister arch::OsxRegisters::rax { "rax", 0x00, 64, false };
const processor::CPURegister arch::OsxRegisters::rbx { "rbx", 0x03, 64, false };
const processor::CPURegister arch::OsxRegisters::rcx { "rcx", 0x01, 64, false };
const processor::CPURegister arch::OsxRegisters::rdx { "rdx", 0x02, 64, false };

const processor::CPURegister arch::OsxRegisters::rsi { "rsi", 0x06, 64, false };
const processor::CPURegister arch::OsxRegisters::rdi { "rdi", 0x07, 64, false };

const processor::CPURegister arch::OsxRegisters::rsp { "rsp", 0x04, 64, false };
const processor::CPURegister arch::OsxRegisters::rbp { "rbp", 0x05, 64, false };

const processor::CPURegister arch::OsxRegisters::r8 { "r8", 0x00, 64, true };
const processor::CPURegister arch::OsxRegisters::r9 { "r9", 0x01, 64, true };
const processor::CPURegister arch::OsxRegisters::r10 { "r10", 0x02, 64, true };
const processor::CPURegister arch::OsxRegisters::r11 { "r11", 0x03, 64, true };
const processor::CPURegister arch::OsxRegisters::r12 { "r12", 0x04, 64, true };
const processor::CPURegister arch::OsxRegisters::r13 { "r13", 0x05, 64, true };
const processor::CPURegister arch::OsxRegisters::r14 { "r14", 0x06, 64, true };
const processor::CPURegister arch::OsxRegisters::r15 { "r15", 0x07, 64, true };