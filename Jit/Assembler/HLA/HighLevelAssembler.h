//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __HighLevelAssembler_H_
#define __HighLevelAssembler_H_

#include <string>
#include <unordered_map>
#include "Variable.h"
#include "GivenCallback.h"
#include "ReturnException.h"
#import "VerbosType.h"
#import "FunctionDefinition.h"
#include "LowLevelAssembler.h"

namespace hla {
    template<class CallbackType>
    class GivenCallback;

    class HighLevelAssembler {
        lla::LowLevelAssembler assembler_;
        sysarch::RegisterAllocator allocator_;
        std::unordered_map<std::string, hla::Variable> variables_;
        const typesys::FunctionDefinition definition_;
        bool allow_new_locals;

    public:
        virtual void initialize() const { }

        void build() {
            // New locals must be defined before this block is run.
            allow_new_locals = false;

            try {
                on_build();
            } catch (hla::ReturnException&) {
                assembler_.ret();
            }

            assembler_.ret();
            assembler_.render();
        }

    protected:
        HighLevelAssembler(byte* memory, typesys::FunctionDefinition definition)
            : assembler_(memory),
            allocator_(assembler_.segment()),
            definition_(definition),
            allow_new_locals(true)
        {

        }

        virtual void on_build() = 0;

        hla::Variable& new_local(const std::string name, const typesys::VerbosType &type) {
            if (!allow_new_locals) {
                throw std::logic_error("cannot create new locals after function is fully constructed");
            }

            variables_.insert({ name, hla::Variable(name, type, allocator_) });

            return variables_.find(name)->second;
        }

        void delete_variable(const hla::Variable &variable) {

        }

        void set_label(std::string name) { std::cout << "set label: " << name << std::endl; }

        GivenCallback<VariableComparison> given(const hla::VariableComparison comparison);

    public:
        void* memory() { return assembler_.memory(); }
        const size_t num_locals() const { return definition_.num_locals(); }
        void ret() const { throw hla::return_exception; }

        void ret(Variable& variable) const { throw hla::return_exception; }
    };
}


#endif //__HighLevelAssembler_H_
