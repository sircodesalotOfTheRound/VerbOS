//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VirtualVariableStackPersistenceStage_H_
#define __VirtualVariableStackPersistenceStage_H_

#include <vector>
#import "VirtualVariable.h"
#include "ProcessorOpCodeSet.h"
#include "OsxRegisters.h"

namespace jit {
    class VirtualVariableStackPersistenceStage {
        std::vector<VirtualVariable> virtual_variables_;

    public:
        VirtualVariableStackPersistenceStage(size_t size)
        {
            virtual_variables_.resize(size);
        }

        VirtualVariable& operator[](int variable_number) {
            if (contains_variable(variable_number)) {
                return virtual_variables_[variable_number];
            }

            throw std::logic_error("Variable is not stack persisted");
        }

        bool contains_variable(int variable_number) {
            return !virtual_variables_[variable_number].is_empty();
        }

        void persist_variable(arch::CpuRegister& from_register, VirtualVariable &&variable) {
            validate_variable(variable);

            // Emit the storage opcode.
            virtual_variables_[variable.variable_number()] = std::move(variable);
        }

        VirtualVariable &&release(int virtual_register_number) {
            if (!contains_variable(virtual_register_number)) {
                throw std::logic_error("virtual register did not contain variable");
            }

            return std::move(virtual_variables_.at(virtual_register_number));
        }

        size_t size() const {
            return virtual_variables_.size();
        }

    private:


        void validate_variable(const VirtualVariable& variable) {
            if (variable.is_empty()) {
                throw std::logic_error("variable content is empty.");
            }

            if (contains_variable(variable.variable_number())) {
                throw std::logic_error("stack already contains this variable");
            }
        }
    };
}


#endif //__VirtualRegisterStackPersistenceStage_H_
