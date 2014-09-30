#include <iostream>
#include "VariableAllocator.h"
#include "VerbajPrimitives.h"
#include "Stackframe.h"
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>

using namespace std;
using namespace op;
using namespace jit;

void* memory();

int main() {
  jit::JitRenderer renderer (memory());
  op::ProcessorOpCodeSet jit_opcodes { };

  jit_opcodes.jmp("first");
  jit_opcodes.mov(arch::OsxRegisters::rax, 100);
  jit_opcodes.label("second");
  jit_opcodes.jmp("last");
  jit_opcodes.label("first");
  jit_opcodes.mov(arch::OsxRegisters::rax, 30);
  jit_opcodes.jmp("second");
  jit_opcodes.label("last");
  jit_opcodes.ret();

  jit_opcodes.render(renderer);
  jit_opcodes.debug_print();
  renderer.debug_print();

  uint64_t (*pfunc)() = (uint64_t(*)())renderer.memory();
  cout << pfunc() << endl;


}