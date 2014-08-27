//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VirtualVariableStackPersistenceStage_H_
#define __VirtualVariableStackPersistenceStage_H_

#include <vector>
#include "VirtualRegister.h"
#import "VirtualVariable.h"

namespace jit {
    class VirtualVariableStackPersistenceStage {
        std::vector<VirtualVariable> virtual_variables_;

    public:
        VirtualVariableStackPersistenceStage(size_t size) {
            virtual_variables_.resize(size);
        }

        bool contains_variable(int virtual_register_number) {
            return !virtual_variables_[virtual_register_number].is_empty();
        }

        void persist_variable(int virtual_register_number, VirtualVariable&& variable) {
            virtual_variables_[virtual_register_number] = std::move(variable);
        }

        VirtualVariable&& retrieve_variable(int virtual_register_number) {
            if (!contains_variable(virtual_register_number)) {
                throw std::logic_error("virtual register did not contain variable");
            }

            VirtualVariable variable = std::move(virtual_variables_[virtual_register_number]);
            return std::move(variable);
        }

        size_t size() const { return virtual_variables_.size(); }
    };
}


#endif //__VirtualRegisterStackPersistenceStage_H_
