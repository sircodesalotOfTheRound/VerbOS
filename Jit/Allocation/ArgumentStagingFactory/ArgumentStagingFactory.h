//
// Created by Reuben Kuhnert on 14/8/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "CpuRegister.h"
#include "Intelx64Registers.h"

#ifndef __ArgumentStagingRegisterAssignmentFactory_H_
#define __ArgumentStagingRegisterAssignmentFactory_H_

namespace jit {
  class ArgumentStagingFactory {
    // Staged arguments are those register-bound variables that
    // are locked to certain registers (because of ABI).
    int staged_argument_count_;

  public:
    ArgumentStagingFactory() : staged_argument_count_(0) {
    }

    const arch::CpuRegister* determine_register() {
      using namespace arch;

      switch (staged_argument_count_++) {
        case 0:
          return &Intelx64Registers::rdi;

        case 1:
          return &Intelx64Registers::rsi;

        case 2:
          return &Intelx64Registers::rdx;

        case 3:
          return &Intelx64Registers::rcx;

        case 4:
          return &Intelx64Registers::r8;

        case 5:
          return &Intelx64Registers::r9;

        case 6:
          return &Intelx64Registers::rax;

        case 7:
          return &Intelx64Registers::r10;

        case 8:
          return &Intelx64Registers::r11;

        case 9:
          return &Intelx64Registers::rbx;

        case 10:
          return &Intelx64Registers::r14;

        case 11:
          return &Intelx64Registers::r15;

        case 12:
          return &Intelx64Registers::r12;

        case 13:
          return &Intelx64Registers::r13;

        default:
          // TODO: Fix this eventually.
          throw std::logic_error("too many arguments");
      }
    }

    void reset() {
      staged_argument_count_ = 0;
    }
  };
}


#endif //__ArgumentStagingRegisterAssignmentFactory_H_
