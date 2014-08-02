//
// Created by Reuben Kuhnert on 14/8/2.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "RegisterAllocator.h"
#include "Variable.h"

void sysarch::RegisterAllocator::with_register(hla::Variable& variable,
        std::function<void(jit::JitCodeSegment&, const sysarch::SystemRegister&)> callback) {

    // If the variable is already staged in a register
    auto staged_variable = staged_variables_.find(variable.name());
    if (staged_variable != staged_variables_.end()) {
        callback(code_segment_, staged_variable->second.sys_register());
    }

        // Otherwise, pop the register then push it again with a new variable
    else {
        RegisterBinding binding = registers_.top();
        registers_.pop();

        // Remove the variable from the staged variable list if available.
        if (binding.has_variable()) {
            hla::Variable& var = binding.variable();
            auto staged_var_index = staged_variables_.find(var.name());

            staged_variables_.erase(staged_var_index);
        }

        binding.variable(variable);
        registers_.push(binding);

        staged_variables_.insert({ variable.name(), binding });
        callback(code_segment_, binding.sys_register());
    }
}

sysarch::RegisterAllocator::RegisterAllocator(jit::JitCodeSegment& segment) : code_segment_(segment) {
    using namespace std;

    registers_.push(osx_registers_.rax);
    registers_.push(osx_registers_.rsi);
    registers_.push(osx_registers_.rdi);
}