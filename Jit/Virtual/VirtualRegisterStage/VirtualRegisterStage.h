//
// Created by Reuben Kuhnert on 14/8/21.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VirtualRegisterStage_H_
#define __VirtualRegisterStage_H_

#include <vector>
#include <queue>
#include <iostream>
#include <functional>
#include "VirtualRegisterBinding.h"
#import "VirtualRegisterCheckout.h"
#include "OsxRegisters.h"
#include "ProcessorOpCodeSet.h"
#import "VirtualStackFrameRegisterSet.h"
#import "VirtualRegisterBindingTable.h"
#import "VirtualRegisterBindingPriorityQueue.h"

namespace jit {
    class VirtualRegisterStage {
        op::ProcessorOpCodeSet& op_codes_;
        int parameter_count_;

        struct VirutalRegisterPtrOps {
            bool operator()(const Ptr_Virtual_Register lhs, const Ptr_Virtual_Register rhs) {
                return lhs->priority() < rhs->priority();
            }
        };

    public:
        VirtualRegisterStage(int parameter_count, op::ProcessorOpCodeSet& op_codes);

        int parameter_count() { return parameter_count_; }

        void insert_at(int index, VirtualRegister virtual_register) {
            // First ensure that the register is empty.
            if (!registers_[index].is_empty()) {
                throw std::logic_error("Invalid program: attempting to overwrite register.");
            }

            registers_[index] = virtual_register;
        }

        void force_binding(int register_index, arch::ConstCpuRegisterRef cpu_register);

        void clear_register(int index) {
            registers_[index] = VirtualRegister::EMPTY;
        }

        void with_register(int register_index, std::function<void(VirtualRegisterCheckoutRef)> callback);
        void with_registers(int lhs, int rhs, std::function<void(VirtualRegisterCheckoutRef,VirtualRegisterCheckoutRef)> callback);

        VirtualRegister& operator[](int index) { return registers_[index]; }

    private:
        VirtualRegisterBinding checkout(int virtual_register_index);
        void release(int register_index, const VirtualRegisterBinding binding);

    private:
        void persist_virtual_register(VirtualRegisterBinding binding);

    private:
        VirtualStackFrameRegisterSet registers_;

        VirtualRegisterBindingPriorityQueue register_queue_;
        VirtualRegisterBindingTable binding_table;
    };
}


#endif //__VirtualRegisterStage_H_
