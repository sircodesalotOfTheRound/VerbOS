//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "Functions.h"

void ::helpers::stack_aligned_call(std::function<void()> callback) {
  uintptr_t top_of_stack = 0;

  __asm { mov [top_of_stack], rsp }

  if (top_of_stack & 0x0F) {
    __asm { sub rsp, 8 }
    callback();
    __asm { add rsp, 8 }

  } else {
    callback();
  }
}

constexpr int helpers::base2_exp(size_t exp) {
  return (0x01 << exp);
}
