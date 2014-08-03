//
// Created by Reuben Kuhnert on 14/7/31.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __Variable_H_
#define __Variable_H_

#include <string>
#include <iostream>
#include "VariableComparison.h"
#include "TypeComparison.h"
#include "VerbosType.h"
#include "RegisterAllocator.h"

namespace sysarch {
    class RegisterAllocator;
}

namespace hla {
    class Variable {
        int priority_ { 1 };
        off_t mem_offset_;

        std::string name_;
        const typesys::VerbosType& type_;
        sysarch::RegisterAllocator& allocator_;

        bool is_persisted_ { false };

    public:
        Variable(std::string name, const typesys::VerbosType& type, sysarch::RegisterAllocator& allocator, off_t mem_offset)
            : name_(name), type_(type), allocator_(allocator), mem_offset_(mem_offset)
        {

        }

        void is_loaded() { allocator_.with_register(*this, [](jit::JitCodeSegment& segment, const sysarch::SystemRegister& reg){
                std::cout << reg << std::endl;
            });
        }

        const std::string name() { return name_; }
        const typesys::VerbosType& def() { return type_; }

        void call(std::string function_name) {std::cout << "calling: " << function_name << std::endl; }
        void operator()() {std::cout << "calling: " << std::endl; }

        void operator=(const uint64_t value) {
            with_register([&](jit::JitCodeSegment& segment, const sysarch::SystemRegister& reg){
                segment.mov(reg, value);
            });
        }

        void operator+=(const uint64_t value) {
            with_register([&](jit::JitCodeSegment &segment, const sysarch::SystemRegister &reg) {
                segment.add(reg, value);
            });
        }

        void operator+=(Variable& rhs) {
            with_register([&](jit::JitCodeSegment &segment, const sysarch::SystemRegister &lreg) {
                allocator_.with_register(rhs, [&](jit::JitCodeSegment &segment, const sysarch::SystemRegister &rreg) {
                    segment.add(lreg, rreg);
                });
            });
        }

        void operator=(const Variable& variable) { std::cout << "assignment" << std::endl; }
        void operator+(const Variable& variable) { std::cout << "assignment" << std::endl; }
        void operator-(const Variable& variable) { std::cout << "assignment" << std::endl; }

        VariableComparison operator==(const Variable& rhs) { return VARIABLE_COMPARISON::EQUALS; }
        VariableComparison operator!=(const Variable& rhs) { return VARIABLE_COMPARISON::EQUALS; }
        VariableComparison operator<(const Variable& rhs) { return VARIABLE_COMPARISON::LESS_THAN; }
        VariableComparison operator<=(const Variable& rhs) { return VARIABLE_COMPARISON::LESS_THAN_OR_EQUALS; }
        VariableComparison operator>(const Variable& rhs) { return VARIABLE_COMPARISON::GREATER_THAN; }
        VariableComparison operator>=(const Variable& rhs) { return VARIABLE_COMPARISON::GREATER_THAN_OR_EQUALS; }

        VariableComparison is_some() { return VARIABLE_COMPARISON::SOME; }
        VariableComparison is_none() { return VARIABLE_COMPARISON::NONE ; }

        TypeComparison is_a(std::string type) { return { TYPE_COMPARISON::ISA, type }; }
        TypeComparison has_a(std::string type) { return { TYPE_COMPARISON::HASA, type }; }
        TypeComparison does_a(std::string type) { return { TYPE_COMPARISON::DOESA, type }; }

        int priority() { return priority_; }
        int mem_offset() { return mem_offset_; }

        bool is_persisted() { return is_persisted_; }
        void is_persisted(bool is) { is_persisted_ = is; }

        friend std::ostream& operator<<(std::ostream& stream, const Variable& variable) {
            return stream << variable.name_ << " : " << variable.type_;
        }

    private:
        void with_register(std::function<void (jit::JitCodeSegment& segment, const sysarch::SystemRegister& reg)> callback) {
            allocator_.with_register(*this, callback);
        }
    };
}

template<>
struct std::hash<hla::Variable> {
    size_t operator()(hla::Variable& variable) {
        std::hash<std::string> hash_function;
        return hash_function(variable.name());
    }
};

#endif //__Variable_H_
