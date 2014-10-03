//
// Created by Reuben Kuhnert on 14/10/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ManagedStack_H__
#define __ManagedStack_H__

#include <thread>
#include "Functions.h"
#include <iostream>

class ManagedThread {
  bool started_;
  bool complete_;
  void* base_address_;
  void*(*entry_point_)();
  void* return_value_;

public:
  ManagedThread(void* entry_point) : entry_point_((void*(*)())entry_point), started_(false), complete_(false) { }

  void start() {
    if (started_) {
      throw std::logic_error("this thread has already been started");
    }

    started_ = true;

    // Call on 16-byte aligned stack.
    helpers::stack_aligned_call([&] {
      // Get the base address:
      __asm {
        mov [base_address_], rbp
      }

      this->return_value_ = entry_point_();
    });

    complete_ = true;
  }

  void* base_address() const {
    if (!started_) {
      throw std::logic_error("thread is not running");
    }

    return base_address_;
  }

  template <class T>
  T return_value() const {
    if (!complete_) {
      throw std::logic_error("Thread must complete running before return value can be read");
    }

    return (T)return_value_;
  }
};


#endif //__ManagedThread_H_
