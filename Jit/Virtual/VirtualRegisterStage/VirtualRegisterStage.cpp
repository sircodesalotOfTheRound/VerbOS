//
// Created by Reuben Kuhnert on 14/8/21.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VirtualRegisterStage.h"

jit::VirtualRegisterStage::VirtualRegisterStage(int parameter_count, op::ProcessorOpCodeSet& op_codes)
        : parameter_count_(parameter_count), op_codes_(op_codes) {

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

    registers_.reserve(10);
}

void jit::VirtualRegisterStage::with_register(int register_index, std::function<void(ConstVirtualRegisterCheckout)> callback) {
    VirtualRegisterBinding binding = checkout(register_index);
    VirtualRegisterCheckout register_checkout { binding.sys_register(), binding.virtual_register() };

    callback(register_checkout);

    release(register_index, binding);
}

void jit::VirtualRegisterStage::with_registers(int lhs, int rhs, std::function<void(ConstVirtualRegisterCheckout, ConstVirtualRegisterCheckout)> callback) {
    VirtualRegisterBinding lhs_binding = checkout(lhs);
    VirtualRegisterBinding rhs_binding = checkout(rhs);

    VirtualRegisterCheckout lhs_checkout { lhs_binding.sys_register(), lhs_binding.virtual_register() };
    VirtualRegisterCheckout rhs_checkout { rhs_binding.sys_register(), rhs_binding.virtual_register() };

    callback (lhs_checkout, rhs_checkout);

    release(lhs, lhs_binding);
    release(rhs, rhs_binding);
}

jit::VirtualRegisterBinding jit::VirtualRegisterStage::checkout(int register_index) {

    // If the requested register is already bound, return it.
    auto binding_iter = mapped_bindings_.find(register_index);
    if (binding_iter != mapped_bindings_.end()) {
        return binding_iter->second;
    }

    // Otherwise grab a binding from the queue:
    VirtualRegisterBinding available_binding = register_queue_.top();
    register_queue_.pop();

    // If the binding is already in use, then free it:
    int bound_virtual_register_number = available_binding.bound_register_number();
    auto existing_binding_iter = mapped_bindings_.find(bound_virtual_register_number);
    if (existing_binding_iter != mapped_bindings_.end()) {
        VirtualRegisterBinding& existing_binding = existing_binding_iter->second;
        // Store the variable to memory
        persist_virtual_register(existing_binding);

        // Erase from current binding list.
        mapped_bindings_.erase(existing_binding_iter);
    }

    // Mark the register as un-saved
    VirtualRegister virtual_register = registers_[register_index];
    virtual_register.is_persisted(false);

    // Bind the data, then add to binding list.
    available_binding.bind(register_index, virtual_register);
    mapped_bindings_.insert({ register_index , available_binding });

    // Return the binding.
    return available_binding;
}

void jit::VirtualRegisterStage::release(int register_index, const VirtualRegisterBinding binding) {
    register_queue_.push(binding);
}

void jit::VirtualRegisterStage::persist_virtual_register(VirtualRegisterBinding binding) {
    VirtualRegister& virtual_register = binding.virtual_register();
    const arch::CpuRegister& cpu_register = binding.sys_register();

    // TODO: Mov opcode to save the register data.
    //op_codes_.mov(arch::OsxRegisters::rax, cpu_register);

    // Mark as persisted
    virtual_register.is_persisted(true);
}