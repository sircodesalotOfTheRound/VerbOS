//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ProcessorOpCodeSet_H_
#define __ProcessorOpCodeSet_H_

#include <vector>
#include <unordered_map>
#include <iostream>
#include <functional>
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
#include "ProcessorAddRegToRegOpCode.h"
#import "ProcessorSubRegToRegOpCode.h"
#import "ProcessorAddConstToRegOpCode.h"
#import "ProcessorSubConstToRegOpCode.h"
#import "ProcessorCallOpCode.h"
#import "MemoryLabel.h"

namespace op {
  class ProcessorOpCodeSet {
    using iterator = std::vector<std::unique_ptr<ProcessorOpCodeBase>>::iterator;
    std::vector<std::unique_ptr<ProcessorOpCodeBase>> opcodes_;
    std::unordered_map<std::string, op::MemoryLabel> labels_;

  public:

    void render(jit::JitRenderer& renderer);
    void clear();
    iterator begin();
    iterator end();

    void debug_print();

  public:
    void ret();

    void label(std::string label);

    void call(void* location) {
      add(new op::ProcessorCallOpCode(location));
    }

    void call(std::string name) {
      add(new op::ProcessorCallOpCode(name));
    }

    void add(arch::ConstCpuRegisterRef lhs, uint64_t rhs);
    void add(arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs);
    void sub(arch::ConstCpuRegisterRef lhs, uint64_t rhs);
    void sub(arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs);
    void mov(arch::ConstCpuRegisterRef sys_register, uint64_t value);
    void mov(arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs);
    void mov(arch::ConstCpuRegisterRef lhs, arch::DereferencedCpuRegister rhs);
    void mov(arch::DereferencedCpuRegister lhs, arch::ConstCpuRegisterRef rhs);
    void inc(arch::ConstCpuRegisterRef sys_register);
    void dec(arch::ConstCpuRegisterRef sys_register);
    void push(arch::ConstCpuRegisterRef sys_register);
    void pop(arch::ConstCpuRegisterRef sys_register);
    void lea(arch::ConstCpuRegisterRef sys_register, const void* object);
    void jmp(std::string label);

    void cmp(arch::ConstCpuRegisterRef lhs, arch::ConstCpuRegisterRef rhs);

    bool contains_label(std::string name) const;
    void add_label(std::string name);
    void add_label(std::string name, void* location);
    void set_label_address(std::string name, void* location);
    void add_label_callback(std::string name, std::function<void(void*)> callback);
    bool label_has_address(std::string name);
    void* get_label_address(std::string name);

  private:
    void add(ProcessorOpCodeBase* op_code) {
      opcodes_.push_back(std::unique_ptr<ProcessorOpCodeBase>(op_code));
    }
  };
}


#endif //__ProcessorOpCodeSet_H_
