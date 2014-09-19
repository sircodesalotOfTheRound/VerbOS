#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VStageArg.h"
#include "VCall.h"
#include "Instance.h"
#include "VerbajPrimitives.h"
#import "VBox.h"
#include "Ldutf8.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
  return mmap(nullptr, (size_t) getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;
using namespace types;

void print(Trait* object) {
  auto& type = object->def();

  if (type.isa("vm.Box<uint64>")) {
    cout << "the boxed value: " << object->data<uint64_t>()[0] << endl;

  }
  else if (type.isa("vm.utf8")) {
    uint64_t length = object->data<uint64_t>()[0];

    for (int index = 0; index != length; ++index) {
      cout << object->data<char>(8)[index];
    }
  }

  cout << endl << "this is a: " << type << endl;
}

void stuff() {

  VirtualStackFrame frame(20);
  JitRenderer renderer(memory());

  frame.insert(new VLdui64(1, 5));
  frame.insert(new VBox(1));
  frame.insert(new VLdutf8(2, "something is amiss"));
  frame.insert(new VStageArg(2));
  frame.insert(new VCall(&print));
  frame.insert(new VRet(2));
  frame.apply(renderer);
  frame.debug_print();

  void (*jit_function)() = (void (*)()) renderer.memory();
  jit_function();
}

int main() {
  VerbajPrimitives::initialize();
  stuff();
}

