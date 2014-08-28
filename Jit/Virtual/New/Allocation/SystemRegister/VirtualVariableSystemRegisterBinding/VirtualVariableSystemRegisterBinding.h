//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "CpuRegister.h"
#include "VirtualVariable.h"

#ifndef __VirtualVariableSystemRegisterBinding_H_
#define __VirtualVariableSystemRegisterBinding_H_

namespace jit {
    class VirtualVariableSystemRegisterBinding {
        static const int none = -1;

        arch::CpuRegister sys_register_;
        int binding_number_;
        VirtualVariable variable_;

    public:
        VirtualVariableSystemRegisterBinding(int binding_number, const arch::CpuRegister &cpu_register) :
                sys_register_(cpu_register),
                binding_number_(binding_number) {

        }


        // Move constructor
        VirtualVariableSystemRegisterBinding(VirtualVariableSystemRegisterBinding &&rhs) :
                sys_register_(rhs.sys_register_),
                binding_number_(rhs.binding_number_),
                variable_(std::move(rhs.variable_))
        {
            rhs.variable_ = VirtualVariable();
            rhs.binding_number_ = none;
        }

        VirtualVariableSystemRegisterBinding& operator=(VirtualVariableSystemRegisterBinding &&rhs) {
            if (this == &rhs) return *this;

            sys_register_ = rhs.sys_register_;
            binding_number_ = rhs.binding_number_;
            variable_ = std::move(rhs.variable_);

            rhs.binding_number_ = none;
            rhs.variable_ = VirtualVariable();

            return *this;
        }


        arch::CpuRegister &sys_register() {
            return sys_register_;
        }

        bool contains_variable() const {
            return !variable_.is_empty();
        }

        VirtualVariable &variable() {
            return variable_;
        }

        VirtualVariable&& release_variable() {
            return std::move(variable_);
        }

        int variable_number() const {
            if (!contains_variable()) {
                throw std::logic_error("register does not contain variable");
            }

            return variable_.variable_number();
        }

        void bind_variable(VirtualVariable &&variable) {
            if (contains_variable()) {
                throw std::logic_error("binding already contains a variable");
            }

            variable_ = std::move(variable);
        }

        int binding_number() const {
            return binding_number_;
        }

        int priority() const {
            if (!contains_variable()) {
                return none;
            }

            return variable_.priority();
        }

    private:
        VirtualVariableSystemRegisterBinding(const VirtualVariableSystemRegisterBinding &) = delete;
        VirtualVariableSystemRegisterBinding operator=(const VirtualVariableSystemRegisterBinding &) = delete;

    };
}


#endif //__VirtualVariableSystemRegisterBinding_H_
