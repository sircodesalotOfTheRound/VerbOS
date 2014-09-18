//
// Created by Reuben Kuhnert on 14/8/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "CpuRegister.h"
#include "OsxRegisters.h"

#ifndef __ArgumentStagingRegisterAssignmentFactory_H_
#define __ArgumentStagingRegisterAssignmentFactory_H_

namespace jit {
  class ArgumentStagingRegisterAssignmentFactory {
    // Staged arguments are those register-bound variables that
    // are locked to certain registers (because of ABI).
    int staged_argument_count_;

  public:
    ArgumentStagingRegisterAssignmentFactory() : staged_argument_count_(0) {
    }

    arch::CpuRegister determine_register() {
      using namespace arch;

      switch (staged_argument_count_++) {
        case 0:
          return OsxRegisters::rdi;

        case 1:
          return OsxRegisters::rsi;

        case 2:
          return OsxRegisters::rdx;

        case 3:
          return OsxRegisters::rcx;

        case 4:
          return OsxRegisters::r8;

        case 5:
          return OsxRegisters::r9;

        case 6:
          return OsxRegisters::rax;

        case 7:
          return OsxRegisters::r10;

        case 8:
          return OsxRegisters::r11;

        case 9:
          return OsxRegisters::rbx;

        case 10:
          return OsxRegisters::r14;

        case 11:
          return OsxRegisters::r15;

        case 12:
          return OsxRegisters::r12;

        case 13:
          return OsxRegisters::r13;

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
