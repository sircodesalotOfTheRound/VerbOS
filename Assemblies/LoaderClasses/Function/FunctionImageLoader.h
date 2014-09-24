//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __FunctionImageLoader_H_
#define __FunctionImageLoader_H_

#include <istream>
#include <sys/mman.h>
#include <unistd.h>
#include "ProcessorOpCodeSet.h"
#include "FileInt8.h"
#include "VirtualStackFrame.h"
#include "VLdui64.h"
#include "VLdutf8.h"
#include "VStageArg.h"
#include "VCall.h"
#include "VRet.h"
#include "Trait.h"
#include "VBox.h"

class FunctionImageLoader {
  std::string name_;
  jit::JitRenderer renderer_;
  jit::VirtualStackFrame frame_;

public:
  FunctionImageLoader(std::istream& stream)
    : name_(FileString(stream)),
    renderer_(memory()), frame_(20) {

    std::cout << name_ << std::endl;
    read_ops(stream);
  }

private:
  void read_ops(std::istream& stream) {
    while (!stream.eof()) {
      frame_.insert(read_opcode(stream));
      stream.peek();
    }
  }

  verbaj::VerbajOpCodeBase* read_opcode(std::istream& stream) {
    using namespace verbaj;

    FileInt8 opcode_value(stream);

    switch ((uint8_t) opcode_value) {
      case 0xd1:
        return VLdutf8::load_op(stream);

      case 0x29:
        return VStageArg::load_op(stream);

      case 0x43:
        return VCall::load_op(stream);

      case 0xc7:
        return VRet::load_op(stream);

      case 0xd3:
        return VLdui64::load_op(stream);

      case 0x31:
        return VBox::load_op(stream);

      default:
        throw std::logic_error("this is not going to work");
    }
  }


  void* memory() {
    return mmap(nullptr, (size_t) getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
  }

public:
  void apply() {
    frame_.apply(renderer_);
  }

  void debug_print() {
    frame_.debug_print();
  }

  void execute() {
    void(*entry_point)() = (void(*)())renderer_.memory();
    entry_point();
  }

  static void print(types::Trait* object);

};


#endif //__FunctionImageLoader_H_
