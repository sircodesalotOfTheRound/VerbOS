//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <vector>
#include "VirtualVariableSystemRegisterBinding.h"
#include "Intelx64Registers.h"
#include "SystemRegisterPriorityQueue.h"
#include "VirtualVariableCheckout.h"

#ifndef __VirtualVariableSystemRegisterStage_H_
#define __VirtualVariableSystemRegisterStage_H_

namespace jit {
  class OsxSystemRegisterPriorityQueue : public SystemRegisterPriorityQueue {

  public:
    OsxSystemRegisterPriorityQueue() {
      using namespace arch;
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(0, Intelx64Registers::rax));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(1, Intelx64Registers::rbx));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(2, Intelx64Registers::rcx));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(3, Intelx64Registers::rdx));

      insert_system_register_binding(VirtualVariableSystemRegisterBinding(4, Intelx64Registers::rsi));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(5, Intelx64Registers::rdi));

      insert_system_register_binding(VirtualVariableSystemRegisterBinding(6, Intelx64Registers::r8));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(7, Intelx64Registers::r9));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(8, Intelx64Registers::r10));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(9, Intelx64Registers::r11));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(10, Intelx64Registers::r12));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(11, Intelx64Registers::r13));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(12, Intelx64Registers::r14));
      insert_system_register_binding(VirtualVariableSystemRegisterBinding(13, Intelx64Registers::r15));
    }
  };
}


#endif //__VirtualVariableSystemRegisterStage_H_
