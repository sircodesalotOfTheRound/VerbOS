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
        op::ProcessorOpCodeSet&jit_opcodes;
        size_t parameter_count_;
        size_t staged_argument_count_;

        struct VirutalRegisterPtrOps {
            bool operator()(const Ptr_Virtual_Register lhs, const Ptr_Virtual_Register rhs) {
                return lhs->priority() < rhs->priority();
            }
        };

    public:
        VirtualRegisterStage(size_t parameter_count, op::ProcessorOpCodeSet& op_codes);

        size_t parameter_count() { return parameter_count_; }

        void insert_at(int index, VirtualRegister virtual_register) {
            // First ensure that the register is empty.
            if (!virtual_registers_[index].is_empty()) {
                throw std::logic_error("Invalid program: attempting to overwrite register.");
            }

            virtual_registers_[index] = virtual_register;
        }

        void force_binding(int register_index, arch::ConstCpuRegisterRef cpu_register);

        void clear_register(int index) {
            virtual_registers_[index] = VirtualRegister::EMPTY;
        }

        void with_register(int register_index, std::function<void(VirtualRegisterCheckoutRef)> callback);
        void with_registers(int lhs, int rhs, std::function<void(VirtualRegisterCheckoutRef,VirtualRegisterCheckoutRef)> callback);

        void stage_argument(int register_index);

        VirtualRegister& operator[](int index) { return virtual_registers_[index]; }

        size_t staged_argument_count() const { return staged_argument_count_; }

    private:
        VirtualRegisterBinding checkout(int virtual_register_index);
        void release(int register_index, ConstVirtualRegisterBindingRef binding);

        off_t calculate_persistence_offset(int virtual_register_number);
        void persist_virtual_register(VirtualRegisterBinding binding);
        void load_virtual_register_from_persistence(VirtualRegisterBinding binding);

    private:
        VirtualStackFrameRegisterSet virtual_registers_;

        VirtualRegisterBindingPriorityQueue register_queue_;
        VirtualRegisterBindingTable binding_table_;
    };
}


#endif //__VirtualRegisterStage_H_
