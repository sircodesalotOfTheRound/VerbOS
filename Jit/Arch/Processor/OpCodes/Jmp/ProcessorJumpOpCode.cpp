//
// Created by Reuben Kuhnert on 14/9/30.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "ProcessorJumpOpCode.h"
#include "ProcessorOpCodeSet.h"

op::ProcessorJumpOpCode::ProcessorJumpOpCode(std::string name, op::ProcessorOpCodeSet& jit_opcodes):
  name_(name),
  jit_opcodes_(jit_opcodes)
{

}

std::string op::ProcessorJumpOpCode::rep() const {
  std::stringstream stream;
  stream << "jmp: " << name_;

  return stream.str();
}

size_t op::ProcessorJumpOpCode::size() const {
  return 0;
}

void op::ProcessorJumpOpCode::render(jit::JitRenderer& renderer) const {
  // TODO: Optimize for short jumps in the future.
  uintptr_t patch_address = (uintptr_t)renderer.current_location();
  uintptr_t end_of_instruction_address = patch_address + 5;

  if (!jit_opcodes_.contains_label(name_)) {
    jit_opcodes_.add_label(name_);

    // Write dummy opcodes here since we're going to patch it over later.
    renderer.write_opcode(0xe9);
    renderer.write_int32(0x00);

    jit_opcodes_.add_label_callback(name_, [=](void* label_address){
      std::cout << "callback" << std::endl;
      // We want to create a new renderer at the captured location.
      jit::JitRenderer renderer_at_memory_location((void*)patch_address);

      renderer_at_memory_location.write_opcode(0xe9);
      renderer_at_memory_location.write_int32((uint32_t)((uintptr_t)label_address - end_of_instruction_address));
    });

  } else {
    uintptr_t label_address = (uintptr_t)jit_opcodes_.get_label_address(name_);

    renderer.write_opcode(0xe9);
    renderer.write_int32((uint32_t)(label_address - end_of_instruction_address));
  }
}
