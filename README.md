# VerbOS

## A brief tour of the verbaj jit compiler

A basic register adding program:

```
// main.cpp
#include <iostream>
#include "Stackframe.h"
#include "MemoryAllocator.h"

using namespace std;
using namespace op;
using namespace jit;
using namespace verbaj;
using namespace types;
using namespace gc;
using namespace arch;

void* request_memory() {
  return mmap(nullptr, (size_t) getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
}


int main() {
  ProcessorOpCodeSet jit_opcodes { };

  const auto rax = Intelx64Registers::rax;
  const auto rbx = Intelx64Registers::rbx;

  jit_opcodes.mov(rax, 10);
  jit_opcodes.mov(rbx, 20);
  jit_opcodes.add(rax, rbx);
  jit_opcodes.ret();

  JitRenderer renderer { request_memory() };
  jit_opcodes.render(renderer);

  jit_opcodes.debug_print();
  cout << endl;
  renderer.debug_print();

  uint64_t(*p_jit_function)() = (uint64_t(*)())renderer.memory();

  cout << endl;
  cout << "the result of the jit function: " << p_jit_function() << endl;
}
```

```
// Output:
mov rax, 0xa
mov rbx, 0x14
add rax, rbx
ret

@100a10000: 48 b8 0a 00 00 00 00 00 00 00 
@100a1000a: 48 bb 14 00 00 00 00 00 00 00 
@100a10014: 48 01 d8 c3 

the result of the jit function: 30
```

## C/C++ Integration

Verbaj can also integrate with existing C/C++ code.

## Memory Access

