# VerbOS

## A brief tour of the verbaj jit compiler

A basic register adding program:

```
#include <iostream>
#include "MemoryAllocator.h"
#include "ProcessorOpCodeSet.h"
#include "Intelx64Registers.h"

using namespace std;
using namespace op;
using namespace jit;
using namespace types;
using namespace gc;
using namespace arch;

void* request_memory() {
  return mmap(nullptr, (size_t) getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
}

void emit_function(ProcessorOpCodeSet& jit_opcodes) {
  const auto rax = Intelx64Registers::rax;
  const auto rbx = Intelx64Registers::rbx;

  jit_opcodes.begin();
  jit_opcodes.mov(rax, 5);
  jit_opcodes.mov(rbx, 20);
  jit_opcodes.add(rax, rbx);
  jit_opcodes.ret();
  jit_opcodes.end();
}

void render_opcodes(JitRenderer& renderer, ProcessorOpCodeSet& jit_opcodes) {
  jit_opcodes.render(renderer);

  cout << "The emitted function (debug):" << endl;
  jit_opcodes.debug_print();
  cout << endl;

  cout << "The emitted memory: " << endl;
  renderer.debug_print();
  cout << endl;
}

int main() {
  void* page_of_memory = request_memory();
  JitRenderer renderer { page_of_memory };
  ProcessorOpCodeSet jit_opcodes { };

  emit_function(jit_opcodes);
  render_opcodes(renderer, jit_opcodes);

  auto p_jit_function = renderer.cast_function<uint64_t(*)()>();

  cout << "The result of the jit_function: " << p_jit_function() << endl;
}
```

```
The emitted function (debug):
mov rax, 0x5
mov rbx, 0x14
add rax, rbx
ret

The emitted memory: 
@108942000: 48 b8 05 00 00 00 00 00 00 00 
@10894200a: 48 bb 14 00 00 00 00 00 00 00 
@108942014: 48 01 d8 c3 

The result of the jit_function: 25
```

## C/C++ Integration

Verbaj can also integrate with existing C/C++ code.

## Memory Access

