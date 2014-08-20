#include "CPURegister.h"
#include "OsxRegisters.h"

const processor::CPURegister arch::OsxRegisters::rax { "rax", 0x00, 64, false  };
const processor::CPURegister arch::OsxRegisters::rbx { "rbx", 0x03, 64, false  };
const processor::CPURegister arch::OsxRegisters::rcx { "rcx", 0x01, 64, false  };
const processor::CPURegister arch::OsxRegisters::rdx { "rdx", 0x02, 64, false  };

const processor::CPURegister arch::OsxRegisters::rsi { "rsi", 0x06, 64, false  };
const processor::CPURegister arch::OsxRegisters::rdi { "rdi", 0x07, 64, false  };

const processor::CPURegister arch::OsxRegisters::rbp { "rbp", 0x07, 64, false  };
const processor::CPURegister arch::OsxRegisters::rsp { "rsp", 0x07, 64, false  };
