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

  jit_opcodes.mov(arch::OsxRegisters::rax, 10);
  jit_opcodes.jmp("start");
  jit_opcodes.mov(arch::OsxRegisters::rax, 10);
  jit_opcodes.label("start");
  jit_opcodes.ret();

  jit_opcodes.render(renderer);
  jit_opcodes.debug_print();
  renderer.debug_print();

  uint64_t (*pfunc)() = (uint64_t(*)())renderer.memory();
  cout << pfunc() << endl;


}