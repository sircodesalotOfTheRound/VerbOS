//
// Created by Reuben Kuhnert on 14/10/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VerbajPrimitives.h"

#ifndef __ExecutionEnvironment_H_
#define __ExecutionEnvironment_H_


class ExecutionEnvironment {
public:
  static bool is_initialized;
  static void initialize() {
    if (is_initialized) {
      return;
    }

    verbaj::VerbajPrimitives::initialize();
    is_initialized = true;
  }
};


#endif //__ExecutionEnvironment_H_
