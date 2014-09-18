#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VStageArg.h"
#include "VCall.h"
#include "Instance.h"
#include "VerbajPrimitives.h"
#import "VBox.h"

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
  auto& type = object->get_instance().type();

  if (type.isa("vm.Box<uint64>")) {
    cout << "the boxed value: " << object->data<uint64_t>()[0] << endl;
  }
}

void stuff() {

  VirtualStackFrame frame(20);
  JitRenderer renderer(memory());

  frame.insert(new VLdui64(1, 5));
  frame.insert(new VBox(1));
  frame.insert(new VStageArg(1));
  frame.insert(new VCall(&print));
  frame.insert(new VRet(1));
  frame.apply(renderer);
  frame.debug_print();

  void (*jit_function)() = (void (*)()) renderer.memory();
  jit_function();
}

int main() {
  VerbajPrimitives::initialize();
  stuff();
}

