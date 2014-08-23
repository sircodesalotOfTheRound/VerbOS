//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ProcessorOpCodeSet_H_
#define __ProcessorOpCodeSet_H_

#include <vector>
#include <unordered_map>
#include <iostream>
#include "ProcessorOpCodeBase.h"
#include "ProcessorReturnOpCode.h"
#include "ProcessorLabelOpCode.h"
#include "ProcessorMovConstToRegOpCode.h"
#include "ProcessorIncOpCode.h"
#include "ProcessorDecOpCode.h"
#include "ProcessorPushOpCode.h"
#include "ProcessorPopOpCode.h"
#import "ProcessorRegToRegMovOp.h"
#import "ProcessorMovRegToMemOp.h"

namespace op {
    class ProcessorOpCodeSet {
        using iterator = std::vector<std::unique_ptr<ProcessorOpCodeBase>>::iterator;

        std::vector<std::unique_ptr<ProcessorOpCodeBase>> opcodes_;

    public:

        void render(jit::JitRenderer& renderer) {
            for (auto& opcode : opcodes_) {
                opcode->render(renderer);
            }
        }

        void clear() { opcodes_.clear(); }

        iterator begin() { return opcodes_.begin(); }
        iterator end() { return opcodes_.end(); }

        void debug_print();

    public:
        // OpCodes
        void ret() { add(new ProcessorReturnOpCode()); }
        void label(std::string label) { add(new ProcessorLabelOpCode(label)); }

        void mov(arch::ConstCpuRegisterRef sys_register, uint64_t value) {
            add(new op::ProcessorMovConstToRegOpCode(sys_register, value));
        }

        void mov(arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs) {
            add(new op::ProcessorRegToRegMovOp(lhs, rhs));
        }

        void mov(arch::ConstCpuRegisterRef lhs, arch::DereferencedCpuRegister rhs) {
            add(new op::ProcessorMovRegToMemOp(lhs, rhs, ProcessorMovRegToMemOp::DIRECTION::FROM_MEMORY));
        }

        void mov(arch::DereferencedCpuRegister lhs, arch::ConstCpuRegisterRef rhs) {
            add(new op::ProcessorMovRegToMemOp(rhs, lhs, ProcessorMovRegToMemOp::DIRECTION::TO_MEMORY));
        }

        void inc(arch::ConstCpuRegisterRef sys_register) {
            add(new op::ProcessorIncOpCode(sys_register));
        }

        void dec(arch::ConstCpuRegisterRef sys_register) {
            add(new op::ProcessorDecOpCode(sys_register));
        }

        void push(arch::ConstCpuRegisterRef sys_register) {
            add(new op::ProcessorPushOpCode(sys_register));
        }

        void pop(arch::ConstCpuRegisterRef sys_register) {
            add(new op::ProcessorPopOpCode(sys_register));
        }

        void lea(arch::ConstCpuRegisterRef sys_register, const void* object) {
            add(new op::ProcessorMovConstToRegOpCode(sys_register, (uintptr_t)object));
        }

    private:
        void add(ProcessorOpCodeBase* op_code) {
            opcodes_.push_back(std::unique_ptr<ProcessorOpCodeBase>(op_code));
        }
    };
}


#endif //__ProcessorOpCodeSet_H_
