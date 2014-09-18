//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "CpuRegister.h"

#ifndef __SystemRegisterPriority_H_
#define __SystemRegisterPriority_H_

namespace jit {
  class SystemRegisterPriority {
    arch::CpuRegister register_;
    int priority_;
    int binding_number_;

  public:
    SystemRegisterPriority(VirtualVariableSystemRegisterBinding& binding)
      : register_(binding.sys_register()),
        priority_(binding.priority() + binding.usage_count()),
        binding_number_(binding.binding_number()) {

    }

    arch::CpuRegister& sys_register() {
      return register_;
    }

    int priority() const {
      return priority_;
    }

    int binding_number() const {
      return binding_number_;
    }

    bool operator<(const SystemRegisterPriority& rhs) const {
      return rhs.priority_ < priority_;
    }
  };
}


#endif //__SystemRegisterPriority_H_
