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
        ArgumentStagingRegisterAssignmentFactory() : staged_argument_count_(0) { }

        arch::CpuRegister determine_register() {
            using namespace arch;

            switch (staged_argument_count_++) {
                case 0:
                    return OsxRegisters::rdi;

                case 1:
                    return OsxRegisters::rsi;

                default:
                    // TODO: Fix this eventually.
                    throw std::logic_error("too many arguments");
            }
        }

        void reset() { staged_argument_count_ = 0; }
    };
}


#endif //__ArgumentStagingRegisterAssignmentFactory_H_
