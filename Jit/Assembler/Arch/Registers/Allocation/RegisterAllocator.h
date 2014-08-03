//
// Created by Reuben Kuhnert on 14/8/2.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __RegisterAllocator_H_
#define __RegisterAllocator_H_

#include <queue>
#include <iostream>
#include <unordered_map>
#include "RegisterBinding.h"
#include "Osx64Registers.h"
#include "SystemRegister.h"
#include "JitCodeSegment.h"

namespace hla {
    class Variable;
}

namespace sysarch {
    class RegisterAllocator {
        jit::JitCodeSegment& code_segment_;
        std::unordered_map<std::string, RegisterBinding> staged_variables_;
        std::priority_queue<RegisterBinding> registers_;

        Osx64Registers osx_registers_;

    public:
        RegisterAllocator(jit::JitCodeSegment& segment);

        void with_register(hla::Variable& variable,
            std::function<void(jit::JitCodeSegment& segment, const sysarch::SystemRegister&)> callback);

        void set_return_value(hla::Variable& variable);

    private:
        void persist_variable(const RegisterBinding& binidng, hla::Variable& variable);
        void retrieve_variable(const RegisterBinding& binidng, hla::Variable& variable);
    };
}


#endif //__RegisterAllocator_H_
