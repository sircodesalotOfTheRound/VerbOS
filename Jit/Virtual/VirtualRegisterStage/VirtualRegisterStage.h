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

namespace jit {
    template<class RegisterType>
    class VirtualRegisterStage {

        struct VirutalRegisterPtrOps {
            bool operator()(const Ptr_Virtual_Register lhs, const Ptr_Virtual_Register rhs) {
                return lhs->priority() < rhs->priority();
            }
        };

    public:
        VirtualRegisterStage() {
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::rax));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::rbx));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::rcx));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::rdx));

            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::rsi));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::rdi));

            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::r8));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::r9));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::r10));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::r11));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::r12));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::r13));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::r14));
            register_queue_.push(VirtualRegisterBinding(arch::OsxRegisters::r15));
        }

        void insert_at(int index, VirtualRegister virtual_register) {
            registers_[index] = virtual_register;
        }

        void clear_register(int index) {
            registers_[index] = VirtualRegister::EMPTY;
        }

        void with_register(int register_index, std::function<void(ConstVirtualRegisterCheckout)> callback) {
            VirtualRegisterBinding binding = checkout(register_index);
            VirtualRegisterCheckout register_checkout { binding.sys_register(), binding.virtual_register() };

            callback(register_checkout);

            release(register_index, binding);
        }

        void with_registers(int lhs, int rhs, std::function<void(ConstVirtualRegisterCheckout, ConstVirtualRegisterCheckout)> callback) {
            VirtualRegisterBinding lhs_binding = checkout(lhs);
            VirtualRegisterBinding rhs_binding = checkout(rhs);

            VirtualRegisterCheckout lhs_checkout { lhs_binding.sys_register(), lhs_binding.virtual_register() };
            VirtualRegisterCheckout rhs_checkout { rhs_binding.sys_register(), rhs_binding.virtual_register() };

            callback (lhs_checkout, rhs_checkout);

            release(lhs, lhs_binding);
            release(rhs, rhs_binding);
        }

    private:
        VirtualRegisterBinding checkout(int register_index) {
            // If the requested register is already bound, return it.
            auto binding_iter = mapped_bindings_.find(register_index);
            if (binding_iter != mapped_bindings_.end()) {
                return binding_iter->second;
            }

            // Otherwise grab a binding from the queue:
            VirtualRegisterBinding available_binding = register_queue_.top();
            register_queue_.pop();

            // If the binding is already in use, then free it:
            int virtual_register_number = available_binding.bound_register_number();
            auto mapped_binding_iter = mapped_bindings_.find(virtual_register_number);
            if (mapped_binding_iter != mapped_bindings_.end()) {
                mapped_bindings_.erase(mapped_binding_iter);
            }

            available_binding.bind(register_index, registers_[register_index]);

            mapped_bindings_.insert({ register_index , available_binding });

            return available_binding;
        }

        void release(int register_index, const VirtualRegisterBinding binding) {
            register_queue_.push(binding);

        }

    private:
        std::array<VirtualRegister, 256> registers_;
        std::priority_queue<VirtualRegisterBinding, std::vector<VirtualRegisterBinding>, std::greater<VirtualRegisterBinding>> register_queue_;
        std::unordered_map<int, VirtualRegisterBinding> mapped_bindings_;
    };
}


#endif //__VirtualRegisterStage_H_
