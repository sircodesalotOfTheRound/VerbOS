//
// Created by Reuben Kuhnert on 14/9/30.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorJumpOpCode_H_
#define __ProcessorJumpOpCode_H_

#include "ProcessorOpCodeBase.h"

namespace op {

  enum JumpType {
    JMP = 0xe9,
    JE = 0x84,
    JNE = 0x85,
    JZ = 0x84,
    JNZ = 0x85,
    JL = 0x8c,
    JG = 0x8f,
    JLE = 0x8e,
    JGE = 0x8d
  };

  class ProcessorOpCodeSet;
  class ProcessorJumpOpCode : public ProcessorOpCodeBase {
    std::string name_;
    JumpType jump_type_;
    ProcessorOpCodeSet& jit_opcodes_;

  public:
    ProcessorJumpOpCode(std::string name, op::ProcessorOpCodeSet& jit_opcodes, JumpType jump_type);

    std::string rep() const;
    size_t size() const;
    void render(jit::JitRenderer&) const;

  private:
    void write_jump_opcode(jit::JitRenderer& renderer) const;
  };
}


#endif //__ProcessorJumpOpCode_H_
