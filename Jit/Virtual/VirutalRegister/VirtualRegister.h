//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <string>
#include "TypeDef.h"
#include "CpuRegister.h"
#include "SystemType.h"

#ifndef __VirtualRegister_H_
#define __VirtualRegister_H_

namespace jit {
    class VirtualRegister {
        int priority_;
        std::string name_;
        mutable const SystemType* type_;
        bool is_empty_;
        bool is_persisted_;
        bool is_pointer_;

    public:
        struct Priority {
            int priority_;
            explicit Priority(int priority) : priority_(priority) { }
        };

        struct Offset {
            ssize_t offset_;
            explicit Offset(ssize_t offset) : offset_(offset) { }
        };

    public:
        VirtualRegister() : VirtualRegister(VirtualRegister::EMPTY) {
        }


        VirtualRegister(std::string name, const SystemType& type, Priority priority, bool is_pointer)
            : name_(name),
              type_(&type),
              priority_(priority.priority_),
              is_empty_(false),
              is_persisted_(false),
              is_pointer_(is_pointer)
        {

        }


        std::string name() const { return name_; }
        int priority() const { return priority_; }
        bool is_empty() const { return is_empty_; }
        const SystemType &def() const { return *type_; }
        bool is_pointer() const { return is_pointer_; }

        friend std::ostream& operator<<(std::ostream& stream, const VirtualRegister& reg) {
            return stream << reg.name_ << " : " << *reg.type_;
        }

        const static VirtualRegister& EMPTY;

        bool is_persisted() { return is_persisted_; }
        void is_persisted(bool persisted) { is_persisted_ = persisted; }

    private:
        VirtualRegister(std::string name, const SystemType& type, int priority, bool is_empty)
            : name_(name),
              type_(&type),
              priority_(priority),
              is_empty_(is_empty)
          {

          }

    };

    using Ptr_Virtual_Register = VirtualRegister*;
    using Const_Virtual_Register = const VirtualRegister;
}


#endif //__VirtualRegister_H_
