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

        // Is this variable a member of some object?
        // (In particular does it require dereferencing to access?)
        bool is_member_;

        // Is this variable a class pointer?
        // That is does it point to the metadata of some class
        // that we can use either for reflection or dynamic programming?
        bool is_class_pointer_;

        // A variable has a parent if it is a member of a class.
        // In terms of our virtual register machine, one register has
        // to contain the location of the parent, and then the variable
        // would contain information about the member.
        int parent_index_;

    public:

        VirtualVariable(int variable_number, const SystemType &type, int priority, bool is_member, bool is_class_pointer) :
                priority_(priority),
                variable_number_(variable_number),
                type_(&type),
                is_empty_(false),
                is_member_(is_member),
                is_class_pointer_(is_class_pointer),
                parent_index_(none)
        {

        }


        // Null-Object
        VirtualVariable() :
                priority_(none),
                variable_number_(none),
                type_(&SystemType::NONE),
                is_empty_(true),
                is_member_(false),
                is_class_pointer_(false),
                parent_index_(none)
        {

        }


        // Only allow movement.
        VirtualVariable(VirtualVariable &&rhs) :
                priority_(rhs.priority_),
                variable_number_(rhs.variable_number_),
                type_(rhs.type_),
                is_empty_(rhs.is_empty_),
                is_member_(rhs.is_member_),
                is_class_pointer_(rhs.is_class_pointer_),
                parent_index_(rhs.parent_index_)
        {
            empty_contents(rhs);
        }

        VirtualVariable &operator=(VirtualVariable &&rhs) {
            if (this == &rhs) return *this;

            // Steal everything form rhs.
            priority_ = rhs.priority_;
            type_ = rhs.type_;
            is_empty_ = rhs.is_empty_;
            variable_number_ = rhs.variable_number_;
            is_member_ = rhs.is_member_;
            is_class_pointer_ = rhs.is_class_pointer_;
            parent_index_ = rhs.parent_index_;

            // Delete rhs.
            empty_contents(rhs);

            return *this;
        }

        int priority() const { return priority_; }
        const SystemType &type() const { return *type_; }
        bool is_empty() const { return is_empty_; }
        int variable_number() const { return variable_number_; }

        bool is_member() const { return is_member_; }
        bool is_class_pointer() const { return is_class_pointer_; }
        bool has_parent() const { return parent_index_ != none; }

    private:

        void empty_contents(VirtualVariable& variable) {
            variable.priority_ = 0;
            variable.type_ = &SystemType::NONE;
            variable.is_empty_ = true;
            variable.variable_number_ = none;
            variable.is_member_ = false;
            variable.is_class_pointer_ = false;
            variable.parent_index_ = none;
        }

        // Disable public copying. Private copy only
        VirtualVariable(const VirtualVariable &rhs) = delete;
        VirtualVariable &operator=(const VirtualVariable &rhs) = delete;
    };
}


#endif //__VirtualVariable_H_
