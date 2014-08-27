//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <iosfwd>
#include "SystemType.h"

#ifndef __VirtualVariable_H_
#define __VirtualVariable_H_

namespace jit {
    class VirtualVariable {
        const static int none = -1;

        int priority_;
        int variable_number_;
        mutable const SystemType *type_;
        bool is_empty_;
        bool is_object_reference_;

    public:

        VirtualVariable(int variable_number, const SystemType &type, int priority, bool is_object_reference) :
                priority_(priority),
                variable_number_(variable_number),
                type_(&type),
                is_empty_(false),
                is_object_reference_(is_object_reference) {

        }


        // Empty
        VirtualVariable() :
                priority_(none),
                variable_number_(none),
                type_(&SystemType::NONE),
                is_empty_(true),
                is_object_reference_(false)
        {

        }


        // Only allow movement.
        VirtualVariable(VirtualVariable &&rhs) :
                priority_(rhs.priority_),
                variable_number_(rhs.variable_number_),
                type_(rhs.type_),
                is_empty_(rhs.is_empty_),
                is_object_reference_(rhs.is_object_reference_)
        {
            empty_contents(rhs);
        }

        VirtualVariable &operator=(VirtualVariable &&rhs) {
            if (this == &rhs) return *this;

            // Steal everything form rhs.
            priority_ = rhs.priority_;
            type_ = rhs.type_;
            is_empty_ = rhs.is_empty_;
            is_object_reference_ = rhs.is_object_reference_;

            // Delete rhs.
            empty_contents(rhs);

            return *this;
        }

        int priority() const { return priority_; }
        const SystemType &type() const { return *type_; }
        bool is_empty() const { return is_empty_; }
        int variable_number() const { return variable_number_; }
        bool is_object_reference() const { return is_object_reference_; }

    private:

        void empty_contents(VirtualVariable& variable) {
            variable.priority_ = 0;
            variable.type_ = &SystemType::NONE;
            variable.is_empty_ = true;
            variable.variable_number_ = none;
            variable.is_object_reference_ = false;
        }

        // Disable public copying. Private copy only
        VirtualVariable(const VirtualVariable &rhs) = delete;

        VirtualVariable &operator=(const VirtualVariable &rhs) = delete;

    };
}


#endif //__VirtualVariable_H_
