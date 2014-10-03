//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VCall.h"
#include "FileString.h"
#include "FunctionTable.h"

void verbaj::VCall::apply(jit::Stackframe& frame) const {
  // Since we need to lock arguments to certain registers, (arg1=rdi, arg2=rsi, etc..)
  // We need to free those registers so they can be used generally.
  frame.allocator().persist_variables();

  // If we have a direct location to jump to:
  // TODO: Read from the function table.
  if (location_ != nullptr && name_.empty()) {
    frame.sys_ops().call(location_);
  } else if (!name_.empty()) {
    frame.sys_ops().call((std::string)name_);
  }
}

verbaj::VCall* verbaj::VCall::load_op(std::istream& stream) {
  using namespace env;

  FileString function_name(stream);

  if (FunctionTable::contains(function_name)) {
    void* function = FunctionTable::get(function_name);
    return new VCall(function);
  }

  else return new VCall(function_name);
}

void verbaj::VCall::patch_call() {
  using namespace std;
  using namespace op;
  using namespace jit;

  // The address that called this function.
  uintptr_t callfrom_location = 0;

  // Read the address that called this function
  // from the call stack.
  __asm {
    mov rax, [rbp + 8]              ; [RBP + 8]: Return address just above RBP.
    sub rax, 5                      ; Subtract 5 from the call address.
    mov [callfrom_location], rax    ; Save the call_from location.
  }

  // Get function call stub name for this location.
  std::string function_name = env::FunctionTable::get_stub_from_location(callfrom_location);
  void* function_entry_point = env::FunctionTable::get(function_name);

  void* memory = (void*)callfrom_location;
  jit::JitRenderer renderer(memory);

  ProcessorCallOpCode call_op(function_entry_point);
  call_op.render(renderer);

  __asm {
    mov rcx, [callfrom_location]    ; Save the return address before smashing the stack
    mov rsp, rbp                    ; Reset the stack pointer
    pop rbp                         ; Set base pointer to previous frame
    add rsp, 8                      ; Delete the return address from stack

    jmp rcx                         ; Jump to the callfrom_location address
  }
}

void verbaj::VCall::render(jit::JitRenderer &emitter) {
  using namespace std;
  using namespace op;

  /*
  uintptr_t call_location = emitter.current_address();
  items_.insert(make_pair(call_location, function_call_));

  emitter.emit(CallOpCode((void *) patch_call));
  */
}
