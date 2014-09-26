//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorCallOpCode.h"
#include "FunctionTable.h"
#include "VCall.h"

void op::ProcessorCallOpCode::render(jit::JitRenderer& renderer) const {
  using namespace std;

  if (function_name_.size() == 0) {
    render_static_call(renderer);
  } else {
    render_call_stub(renderer);
  }
}

std::string op::ProcessorCallOpCode::rep() const {
  std::stringstream stream;
  stream << "call: (offset " << std::hex << call_offset_ << ") ";

  return stream.str();
}

size_t op::ProcessorCallOpCode::size() const {
  return 5;
}

void op::ProcessorCallOpCode::render_static_call(jit::JitRenderer& renderer) const {
  //uintptr_t current_memory_location = (uintptr_t) renderer.current_location();
  call_offset_ = (uint32_t)determine_call_offset((uintptr_t) renderer.current_location(), static_location_);
  //(uint32_t) (static_location_ - (current_memory_location + opcode_size));

  renderer.write_opcode(0xe8);
  renderer.write_int32(call_offset_);
}

void op::ProcessorCallOpCode::render_call_stub(jit::JitRenderer& renderer) const {
  static uintptr_t to_location = (uintptr_t)&verbaj::VCall::patch_call;
  uintptr_t current_location = (uintptr_t) renderer.current_location();
  call_offset_ = (uint32_t) determine_call_offset(current_location, to_location);

  env::FunctionTable::add_stub(current_location, function_name_);

  renderer.write_opcode(0xe8);
  renderer.write_int32(call_offset_);
}
