//
// Created by Reuben Kuhnert on 14/8/2.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "SystemRegister.h"

#ifndef __Osx64Registers_H_
#define __Osx64Registers_H_

namespace sysarch {
    struct Osx64Registers {
        const size_t word_size = 64;

        SystemRegister rax { "rax", 0x00, 64, false };
        const SystemRegister rbx { "rbx", 0x03, 64, false };
        const SystemRegister rcx { "rcx", 0x01, 64, false };
        const SystemRegister rdx { "rdx", 0x02, 64, false };

        const SystemRegister eax { "eax", 0x00, 32, false };
        const SystemRegister ebx { "ebx", 0x03, 32, false };
        const SystemRegister ecx { "ecx", 0x01, 32, false };
        const SystemRegister edx { "edx", 0x02, 32, false };

        const SystemRegister ax { "ax", 0x00, 16, false };
        const SystemRegister bx { "bx", 0x03, 16, false };
        const SystemRegister cx { "cx", 0x01, 16, false };
        const SystemRegister dx { "dx", 0x02, 16, false };

        const SystemRegister al { "al", 0x00, 8, false };
        const SystemRegister bl { "bl", 0x03, 8, false };
        const SystemRegister cl { "cl", 0x01, 8, false };
        const SystemRegister dl { "dl", 0x02, 8, false };

        const SystemRegister ah { "ah", 0x04, 8, false };
        const SystemRegister bh { "bh", 0x07, 8, false };
        const SystemRegister ch { "ch", 0x05, 8, false };
        const SystemRegister dh { "dh", 0x06, 8, false };

        const SystemRegister rbp { "rbp", 0x05, 8, false };
        const SystemRegister rsp { "rsp", 0x04, 8, false };

        SystemRegister rdi { "rdi", 0x07, 8, false };
        SystemRegister rsi { "rsi", 0x06, 8, false };

        // Extended Registers
        const SystemRegister r8  { "r8", 0x00, 64, true };
        const SystemRegister r9  { "r9", 0x01, 64, true };
        const SystemRegister r10 { "r10", 0x02, 64, true };
        const SystemRegister r11 { "r11", 0x03, 64, true };
        const SystemRegister r12 { "r12", 0x04, 64, true };
        const SystemRegister r13 { "r13", 0x05, 64, true };
        const SystemRegister r14 { "r14", 0x06, 64, true };
        const SystemRegister r15 { "r15", 0x07, 64, true };
    };
}


#endif //__Osx64Registers_H_
