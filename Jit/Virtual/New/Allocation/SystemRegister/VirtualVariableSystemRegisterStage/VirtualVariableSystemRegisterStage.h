//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <vector>
#include "VirtualVariableSystemRegisterBinding.h"
#include "OsxRegisters.h"
#include "SystemRegisterPriorityQueue.h"
#include "VirtualVariableCheckout.h"

#ifndef __VirtualVariableSystemRegisterStage_H_
#define __VirtualVariableSystemRegisterStage_H_

namespace jit {
    class VirtualVariableSystemRegisterStage {
        SystemRegisterPriorityQueue register_queue_;

    public:
        VirtualVariableSystemRegisterStage() {
            using namespace arch;
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(0, OsxRegisters::rax));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(1, OsxRegisters::rbx));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(2, OsxRegisters::rcx));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(3, OsxRegisters::rdx));

            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(4, OsxRegisters::rsi));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(5, OsxRegisters::rdi));

            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(6, OsxRegisters::r8));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(7, OsxRegisters::r9));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(8, OsxRegisters::r10));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(9, OsxRegisters::r11));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(10, OsxRegisters::r12));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(11, OsxRegisters::r13));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(12, OsxRegisters::r14));
            register_queue_.insert_system_register_binding(VirtualVariableSystemRegisterBinding(13, OsxRegisters::r15));
        }

        void with_register(int virtual_register_number, std::function<void(VirtualVariableCheckout&)>& callback) {
            VirtualVariableCheckout checkout = register_queue_.borrow(virtual_register_number);

            callback(checkout);
        }

        void with_register(int lhs_register_number, int rhs_register_number,
            std::function<void(VirtualVariableCheckout&, VirtualVariableCheckout&)>& callback) {

            VirtualVariableCheckout lhs = register_queue_.borrow(lhs_register_number);
            VirtualVariableCheckout rhs = register_queue_.borrow(rhs_register_number);

            callback(lhs, rhs);
        }
        
        
        bool is_bound(int virtual_register_number) {
            return register_queue_.is_bound(virtual_register_number);
        }
        
        VirtualVariableSystemRegisterBinding&& dequeue_binding() {
            VirtualVariableSystemRegisterBinding&& binding = std::move(register_queue_.dequeue_binding());

            return std::move(binding);
        }

        void bind(VirtualVariableSystemRegisterBinding&& binding) {
            register_queue_.bind(std::move(binding));
        }
        
        VirtualVariable&& unbind(int virtual_variable_number) {
            return register_queue_.unbind(virtual_variable_number);
        }

    };
}


#endif //__VirtualVariableSystemRegisterStage_H_
