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


  jit_opcodes.cmp(arch::Intelx64Registers::rax, arch::Intelx64Registers::rax);
  jit_opcodes.cmp(arch::Intelx64Registers::rax, arch::Intelx64Registers::rbx);
  jit_opcodes.cmp(arch::Intelx64Registers::rbx, arch::Intelx64Registers::rcx);
  jit_opcodes.cmp(arch::Intelx64Registers::rax, arch::Intelx64Registers::r8);
  jit_opcodes.cmp(arch::Intelx64Registers::r8, arch::Intelx64Registers::rax);
  jit_opcodes.cmp(arch::Intelx64Registers::r8, arch::Intelx64Registers::r8);

  jit_opcodes.render(renderer);
  jit_opcodes.debug_print();
  renderer.debug_print();
}