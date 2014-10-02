//
// Created by Reuben Kuhnert on 14/8/25.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VStageArg.h"
#include "FileInt8.h"
#include "Stackframe.h"

void verbaj::VStageArg::apply(jit::Stackframe& frame) const {
  auto& stage = frame.allocator();
  stage.stage_argument(variable_number);
}

verbaj::VStageArg* verbaj::VStageArg::load_op(std::istream& stream) {
  FileInt8 variable_number(stream);

  return new VStageArg(variable_number);
}
