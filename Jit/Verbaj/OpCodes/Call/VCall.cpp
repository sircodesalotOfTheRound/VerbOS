//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VCall.h"
#include "VirtualStackFrame.h"
#include "FileString.h"
#import "FunctionTable.h"

void verbaj::VCall::apply(jit::VirtualStackFrame& frame) const {
  // Since we need to lock arguments to certain registers, (arg1=rdi, arg2=rsi, etc..)
  // We need to free those registers so they can be used generally.
  frame.variable_stage().persist_variables();

  // Make the call
  frame.sys_ops().call(location_);
}

verbaj::VCall* verbaj::VCall::load_op(std::istream& stream) {
  FileString function_name(stream);

  void* function = env::FunctionTable::get(function_name);
  return new VCall(function);
}
