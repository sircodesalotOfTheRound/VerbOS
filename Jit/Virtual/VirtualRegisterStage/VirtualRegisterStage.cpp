//
// Created by Reuben Kuhnert on 14/8/21.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VirtualRegisterStage.h"

jit::VirtualRegisterStage::VirtualRegisterStage(size_t parameter_count, op::ProcessorOpCodeSet &op_codes)
        : parameter_count_(parameter_count), op_codes_(op_codes),
          registers_(10, 10, 10, 10) {
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

void jit::VirtualRegisterStage::with_register(int register_index, std::function<void(VirtualRegisterCheckoutRef)> callback) {
    VirtualRegisterBinding binding = checkout(register_index);
    VirtualRegisterCheckout register_checkout{binding.sys_register(), binding.virtual_register(), op_codes_};

    callback(register_checkout);

    release(register_index, binding);
}

void jit::VirtualRegisterStage::with_registers(int lhs, int rhs, std::function<void(VirtualRegisterCheckoutRef, VirtualRegisterCheckoutRef)> callback) {
    VirtualRegisterBinding lhs_binding = checkout(lhs);
    VirtualRegisterBinding rhs_binding = checkout(rhs);

    VirtualRegisterCheckout lhs_checkout{lhs_binding.sys_register(), lhs_binding.virtual_register(), op_codes_};
    VirtualRegisterCheckout rhs_checkout{rhs_binding.sys_register(), rhs_binding.virtual_register(), op_codes_};

    callback(lhs_checkout, rhs_checkout);

    release(lhs, lhs_binding);
    release(rhs, rhs_binding);
}

jit::VirtualRegisterBinding jit::VirtualRegisterStage::checkout(int virtual_register_index) {
    // (1) If the virtual-reg is already bound to a cpu-reg, return that binding.
    if (binding_table.is_bound(virtual_register_index)) {
        return binding_table[virtual_register_index];
    }

    // (2) Otherwise grab an available binding from the queue (lowest priority):
    VirtualRegisterBinding binding = register_queue_.pop();

    // (3) If something else is already bound to it, persist, then free that binding.
    if (!binding.is_empty()) {
        // Store the variable to memory
        persist_virtual_register(binding);

        // Delete the existing binding
        binding_table.remove_binding(binding);
    }

    // Mark the register as modified (not-persisted).
    VirtualRegister virtual_register = registers_[virtual_register_index];
    virtual_register.is_persisted(false);

    // Bind the data, then add to binding list.
    binding.bind(virtual_register_index, virtual_register);
    binding_table.insert_binding(binding);

    // Return the binding.
    return binding;
}

void jit::VirtualRegisterStage::release(int register_index, const VirtualRegisterBinding binding) {
    register_queue_.push(binding);
}

void jit::VirtualRegisterStage::persist_virtual_register(VirtualRegisterBinding binding) {
    VirtualRegister &virtual_register = binding.virtual_register();
    //const arch::CpuRegister& cpu_register = binding.sys_register();

    // TODO: Mov opcode to save the register data.
    //op_codes_.mov(arch::OsxRegisters::rax, cpu_register);

    // Mark as persisted
    virtual_register.is_persisted(true);
}

void jit::VirtualRegisterStage::force_binding(int register_index, arch::CpuRegister const &cpu_register) {
    /*// First clear whatever bindings the virtual/cpu registers might be tied to.
    if (binding_table.is_bound(register_index)) {
        persist_virtual_register(binding_table[register_index]);
    }

    if (binding_table.is_bound(cpu_register)) {
        persist_virtual_register(cpu_register);
    }

    */
}

void jit::VirtualRegisterStage::stage_argument(int register_index) {
    const arch::CpuRegister* binding_register;

    switch (staged_argument_count_) {
        case 1:
            binding_register = &arch::OsxRegisters::rdi;
            break;

        case 2:
            binding_register = &arch::OsxRegisters::rsi;
            break;

        default:
            throw std::logic_error("invalid argument");
    }

    if (binding_table.is_bound(register_index)) {

    }
}
