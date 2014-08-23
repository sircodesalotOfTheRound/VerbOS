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
#include "ProcessorMovOpCode.h"
#include "ProcessorIncOpCode.h"
#include "ProcessorDecOpCode.h"
#include "ProcessorPushOpCode.h"
#include "ProcessorPopOpCode.h"

namespace op {
    class ProcessorOpCodeSet {
        using iterator = std::vector<std::unique_ptr<ProcessorOpCodeBase>>::iterator;

        std::vector<std::unique_ptr<ProcessorOpCodeBase>> op_codes_;

    public:

        void render(jit::JitRenderer& renderer) {
            for (auto& opcode : op_codes_) {
                opcode->render(renderer);
            }
        }

        iterator begin() { return op_codes_.begin(); }
        iterator end() { return op_codes_.end(); }

    public:
        // OpCodes
        void ret() { add(new ProcessorReturnOpCode()); }
        void label(std::string label) { add(new ProcessorLabelOpCode(label)); }
        void mov(const arch::CpuRegister& sys_register, uint64_t value) {
            add(new op::ConstToRegProcessorMovOpCode(sys_register, value));
        }

        void inc(const arch::CpuRegister& sys_register) {
            add(new op::ProcessorIncOpCode(sys_register));
        }

        void dec(const arch::CpuRegister& sys_register) {
            add(new op::ProcessorDecOpCode(sys_register));
        }

        void push(const arch::CpuRegister& sys_register) {
            add(new op::ProcessorPushOpCode(sys_register));
        }

        void pop(const arch::CpuRegister& sys_register) {
            add(new op::ProcessorPopOpCode(sys_register));
        }

    private:
        void add(ProcessorOpCodeBase* op_code) {
            op_codes_.push_back(std::unique_ptr<ProcessorOpCodeBase>(op_code));
        }
    };
}


#endif //__ProcessorOpCodeSet_H_
