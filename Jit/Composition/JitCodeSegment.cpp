//
// Created by Reuben Kuhnert on 14-6-18.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "JitCodeSegment.h"

void jit::JitCodeSegment::add(sysarch::const_sys_register lhs, sysarch::const_sys_register rhs) {
    add_opcode(new AddOpCode(lhs, rhs));
}

void jit::JitCodeSegment::sub(sysarch::const_sys_register lhs, sysarch::const_sys_register rhs) {
    add_opcode(new SubOpCode(lhs, rhs));
}

void jit::JitCodeSegment::sub(sysarch::const_sys_register reg, uint64_t size) {
    add_opcode(new SubOpCode(reg, size));
}

void jit::JitCodeSegment::push( sysarch::const_sys_register reg) {
    add_opcode(new PushOpCode(reg));
}

void jit::JitCodeSegment::push(int32 value) {
    add_opcode(new PushOpCode(value));
}

void jit::JitCodeSegment::pop( sysarch::const_sys_register reg) {
    add_opcode(new PopOpCode(reg));
}

void jit::JitCodeSegment::call( sysarch::p_sys_register reg) {
    add_opcode(new CallOpCode(reg));
}

void jit::JitCodeSegment::mov( sysarch::const_sys_register reg, int64 value) {
    add_opcode(new MovOpCode(reg, value));
}

void jit::JitCodeSegment::mov( sysarch::const_sys_register destination, sysarch::const_sys_register source) {
    add_opcode(new MovOpCode(destination, source));
}

void jit::JitCodeSegment::lea( sysarch::const_sys_register lhs, void *rhs) {
    this->mov(lhs, (uintptr_t) &*rhs);
}

void jit::JitCodeSegment::syscall() {
    add_opcode(new SyscallOpCode());
}

void jit::JitCodeSegment::ret() {
    add_opcode(new ReturnOpCode());
}

void jit::JitCodeSegment::begin_frame() {
    using namespace sysarch;

    push(registers_.rbp);
    mov(registers_.rbp, registers_.rsp);

    // Todo: make frame size not fixed.
    //add(registers_.rsp, 256);
}

void jit::JitCodeSegment::end_frame() {
    using namespace sysarch;

    // Todo: make frame size not fixed.
    //sub(registers_.rsp, 256);

    pop(registers_.rbp);
    ret();
}

void jit::JitCodeSegment::emit_to(JitEmitter &writer) {
    for (OpCode *opcode : _opcodes) {
        opcode->render(writer);
    }
}


jit::JitCodeSegment::~JitCodeSegment() {
    for (OpCode *opcode : _opcodes) {
        delete opcode;
    }
}

void jit::JitCodeSegment::add(sysarch::const_sys_register lhs, const uint64 rhs) {
    add_opcode(new AddOpCode(lhs, rhs));
}

void jit::JitCodeSegment::call(CallStub* stub) {
    add_opcode(stub);
}

jit::JitCodeSegment::JitCodeSegment() {

}

void jit::JitCodeSegment::mov( sysarch::const_sys_register lhs, sysarch::DereferencedRegister rhs) {
    if (rhs.has_offset())
        add_opcode(new MovDerefOpcode(lhs, rhs.sys_register(), MovDerefOpcode::DEREF_SOURCE, rhs.offset()));
    else
        add_opcode(new MovDerefOpcode(lhs, rhs.sys_register(), MovDerefOpcode::DEREF_SOURCE));
}

void jit::JitCodeSegment::mov( sysarch::DereferencedRegister lhs, sysarch::const_sys_register rhs) {
    if (lhs.has_offset())
        add_opcode(new MovDerefOpcode(lhs.sys_register(), rhs, MovDerefOpcode::DEREF_DESTINATION, lhs.offset()));
    else
        add_opcode(new MovDerefOpcode(lhs.sys_register(), rhs, MovDerefOpcode::DEREF_DESTINATION));
}
