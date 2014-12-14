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

Verbaj can also integrate with existing C/C++ code. Here we'll use a simple factorial function:

```
int factorial(int value) {
  if (value < 2) return 1;
  return factorial(value - 1) * value;
}
```

and we'll modify our code to use this function:

```
void emit_function(ProcessorOpCodeSet& jit_opcodes) {
  const auto rdi = Intelx64Registers::rdi;

  jit_opcodes.begin();
  jit_opcodes.mov(rdi , 5);
  jit_opcodes.call((void*)factorial);
  jit_opcodes.ret();
  jit_opcodes.end();
}
```

The resulting output:

```
The emitted function (debug):
mov rdi, 0x5
call: (offset ffee9af1) 
ret

The emitted memory: 
@10991f000: 48 bf 05 00 00 00 00 00 00 00 
@10991f00a: e8 f1 9a ee ff c3 

The result of the jit_function: 120
```

## Memory Access

Verbaj can also access memory directly declared in C/C++ code. The following example displays values using the helper function `display`:

```
void display(uint8_t value) {
  helpers::stack_aligned_call([&] {
    cout << "the value is: " << (int) value << endl;
  });
}
```

Notice that display requires the use of the function `helpers::stack_aligned_call` because System V/OSX require calls to the operating system (`cout` calls the posix `write` function downstream) to be stack-aligned to a 16 byte address.

The code for our jit function:

```
void emit_function(ProcessorOpCodeSet& jit_opcodes) {
  static uint8_t numbers[] { 1, 2, 3, 4, 5 };
  static uint8_t index = 0;

  const auto& rdi = Intelx64Registers::rdi;
  const auto& rax = Intelx64Registers::rax;
  const auto& rbx = Intelx64Registers::rbx;
  const auto& rcx = Intelx64Registers::rcx;
  const auto& rdx = Intelx64Registers::rdx;
  const auto& rsp = Intelx64Registers::rsp;


  jit_opcodes.begin();

  // for (int index = 0; index != 5; ++index) {
  //   display(numbers[index]);
  // }
  jit_opcodes.label("start");

  jit_opcodes.lea(rcx, &index);         // Load the address for 'index'
  jit_opcodes.mov(rcx, *rcx);           // Dereference 'index'
  jit_opcodes.lea(rdi, &numbers);       // Load the address for numbers
  jit_opcodes.add(rdi, rcx);            // Add the index offset to numbers.
  jit_opcodes.mov(rdi, *rdi);           // Dereference address
  jit_opcodes.call((void*)display);     // Call display

  jit_opcodes.lea(rcx, &index);         // Load the address for 'index'
  jit_opcodes.mov(rdx, *rcx);           // Dereference 'index' into rdx.
  jit_opcodes.inc(rdx);                 // increment index
  jit_opcodes.mov(*rcx, rdx);           // Persist the value of index.
  jit_opcodes.mov(rax, 5);              // Load the value '5'
  jit_opcodes.cmp(rdx, rax);            // Compare index with '5'.
  jit_opcodes.jl("start");

  jit_opcodes.ret();
  jit_opcodes.end();
}
```

The outputted information:

```
The emitted function (debug):
start: 
mov rcx, 0x105f94878
mov rcx, [rcx0]
mov rdi, 0x105f93a50
add rdi, rcx
mov rdi, [rdi0]
call: (offset ffee5e5e) 
mov rcx, 0x105f94878
mov rdx, [rcx0]
inc
mov [rcx0], rdx
mov rax, 0x5
cmp rdx, rax
jl: start
ret

The emitted memory: 
@10603a000: 48 b9 78 48 f9 05 01 00 00 00 
@10603a00a: 48 8b 09 48 bf 50 3a f9 05 01 
@10603a014: 00 00 00 48 01 cf 48 8b 3f e8 
@10603a01e: 5e 5e ee ff 48 b9 78 48 f9 05 
@10603a028: 01 00 00 00 48 8b 11 48 ff c2 
@10603a032: 48 89 11 48 b8 05 00 00 00 00 
@10603a03c: 00 00 00 48 39 c2 0f 8c b8 ff 
@10603a046: ff ff c3 

the value is: 1
the value is: 2
the value is: 3
the value is: 4
the value is: 5
```

## Verba/Verbatim integration

The verbaj compiler is designed for the verba langauge verbatim byte code literature files. The following is an example using actual verbatim byte codes.

```
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <fstream>

#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VStageArg.h"
#include "VCall.h"
#include "Instance.h"
#include "VerbajPrimitives.h"
#include "VBox.h"
#include "VLdutf8.h"
#include "FunctionImageLoader.h"
#include "FunctionTable.h"
#include "VerbajFile.h"
#include "ManagedStack.h"
#include "ExecutionEnvironment.h"
#include "VCopy.h"

void* memory() {
  return mmap(nullptr, (size_t) getpagesize(),
    PROT_WRITE | PROT_EXEC,
    MAP_ANON | MAP_PRIVATE, -1, 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;
using namespace types;
using namespace env;

// Print uses reflection to determine what type of object it's displaying.
void print(Trait* object) {
  auto& type = object->def();

  if (type.isa(VerbajPrimitives::vm_box_of_uint64)) {
    cout << "the boxed value: " << object->data<uint64_t>()[0];

  }
  else if (type.isa(VerbajPrimitives::vm_utf8)) {
    uint64_t length = object->data<uint64_t>()[0];

    for (int index = 0; index != length; ++index) {
      cout << object->data<char>(8)[index];
    }
  }
}

void println(Trait* object) {
  print(object);

  cout << endl;
}

int main() {
  ExecutionEnvironment::initialize();

  // This stackframe uses 20 garbage collectable registers.
  // And 5 non-collectable (constants such as ints).
  Stackframe frame(20, 5);
  JitRenderer renderer(memory());

  // Load an int, box it, and then call 'println'.
  frame.insert(new VLdui64(1, 42));
  frame.insert(new VBox(1));
  frame.insert(new VStageArg(1));
  frame.insert(new VCall((void*)&println));

  // Load an utf8, and then call 'println'.
  frame.insert(new VLdui64(1, 5));
  frame.insert(new VLdutf8(2, "The quick brown fox jumps over the lazy dog"));
  frame.insert(new VStageArg(2));
  frame.insert(new VCall((void*)&println));

  // Return the value in register #1.
  frame.insert(new VRet(1));

  frame.apply(renderer);
  frame.debug_print();

  // Start the managed stack on another thread.
  cout << endl;
  ManagedThread thread(renderer.memory());
  thread.start();
}
```

The following is the output of the previous code:

```
push rbp
mov rbp, rsp
sub rsp, 256
mov rbx, 0x2a
mov rdi, rbx
mov [rbp-16], rdi
call: (offset fff0ef4f) 
mov r15, rax
mov [rbp-16], r15
mov rdi, r15
mov [rbp-16], rdi
call: (offset fff22b4c) 
mov r14, 0x5
mov rdi, 0x7f8b22500cd8
mov [rbp-16], r14
mov [rbp-24], rdi
call: (offset fff22b2b) 
mov rsi, [rbp-16]
mov rax, rsi
add rsp, 256
pop rbp
ret

the boxed value: 42
The quick brown fox jumps over the lazy dog
```
