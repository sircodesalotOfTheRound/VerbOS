#include <iostream>
#include "VariableAllocator.h"
#include "VerbajPrimitives.h"
#include "Stackframe.h"
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;
using namespace op;
using namespace jit;

void* memory();

int main() {
  jit::JitRenderer renderer (memory());
  op::ProcessorOpCodeSet jit_opcodes { };

  jit_opcodes.label("start");
  jit_opcodes.jmp("start");
  jit_opcodes.je("start");
  jit_opcodes.jne("start");
  jit_opcodes.jz("start");
  jit_opcodes.jnz("start");
  jit_opcodes.jl("start");
  jit_opcodes.jg("start");
  jit_opcodes.jle("start");
  jit_opcodes.jge("start");

  jit_opcodes.render(renderer);
  jit_opcodes.debug_print();
  renderer.debug_print();

}
