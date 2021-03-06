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
#include "VLdui64.h"
#include "VLdutf8.h"
#include "VStageArg.h"
#include "VCall.h"
#include "VRet.h"
#include "Trait.h"
#include "VBox.h"
#include "ObjectImage.h"

namespace images {
  class FunctionImageLoader : public ObjectImage {
    std::string name_;
    jit::JitRenderer renderer_;
    jit::Stackframe frame_;

  public:
    FunctionImageLoader(std::istream& stream)
      : name_(FileString(stream)),
      renderer_(memory()), frame_(20, 5) {

      read_ops(stream);
    }

    void* entry_point() {
      return renderer_.memory();
    }

    std::string image_name() const override { return name_; }

    void* compile() {
      frame_.apply(renderer_);
      return entry_point();
    }

    void debug_print() {
      frame_.debug_print();

      std::cout << "core dump @" << renderer_.memory() << ": " << std::endl;
      renderer_.debug_print();
    }

    void execute() {
      void(*entry_point)() = (void(*)())renderer_.memory();
      entry_point();
    }

    static void print(types::Trait* object);


  private:
    void read_ops(std::istream& stream) {
      while (!stream.eof()) {
        frame_.insert(read_opcode(stream));

        if (is_function_eof_opcode(stream)) {
          break;
        }
      }
    }

    bool is_function_eof_opcode(std::istream& stream) const {
      int peeked_value = stream.peek();

      // Consume value if matching.
      if (peeked_value == 0xFF) {
        stream.get();
        return true;
      }

      return false;
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
  };
}


#endif //__FunctionImageLoader_H_
