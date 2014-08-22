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
        ssize_t offset_;

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
        VirtualRegister() : VirtualRegister(VirtualRegister::EMPTY) { }


        VirtualRegister(std::string name, const SystemType& type, Priority priority, Offset offset)
            : name_(name),
              type_(&type),
              priority_(priority.priority_),
              offset_(offset.offset_),
              is_empty_(false)
        {

        }

        VirtualRegister(const VirtualRegister& rhs)
            : name_(rhs.name_),
              type_(rhs.type_),
              priority_(rhs.priority_),
              is_empty_(rhs.is_empty_)
        {

        }

        VirtualRegister& operator=(const VirtualRegister& rhs) {
            if (this == &rhs) return *this;

            name_ = rhs.name_;
            type_ = rhs.type_;
            priority_ = rhs.priority_;
            is_empty_ = rhs.is_empty_;
            offset_ = rhs.offset_;

            return *this;
        }

        std::string name() const { return name_; }
        int priority() const { return priority_; }
        bool is_empty() { return is_empty_; }
        ssize_t offset() { return offset_; }
        const SystemType &def() const { return *type_; }

        friend std::ostream& operator<<(std::ostream& stream, const VirtualRegister& reg) {
            return stream << reg.name_ << " : " << *reg.type_;
        }

        const static VirtualRegister& EMPTY;



    private:
        VirtualRegister(std::string name, const SystemType& type, int priority, bool is_empty, ssize_t offset)
            : name_(name),
              type_(&type),
              priority_(priority),
              offset_(offset),
              is_empty_(is_empty)
          {

          }

    };

    using Ptr_Virtual_Register = VirtualRegister*;
    using Const_Virtual_Register = const VirtualRegister;
}


#endif //__VirtualRegister_H_
