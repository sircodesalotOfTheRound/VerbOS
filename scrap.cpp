
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VStageArg.h"
#include "VCall.h"
#include "Instance.h"
#include "VerbajPrimitives.h"
#include "VBox.h"
#include "VLdutf8.h"
#include <fstream>
#import "FunctionImageLoader.h"
#import "FunctionTable.h"
#include "VerbajFile.h"
#import "Event.h"
#import "Collector.h"

void* memory() {
  return mmap(nullptr, (size_t) getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;
using namespace types;
using namespace env;

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

void stuff() {

  VirtualStackFrame frame(20);
  JitRenderer renderer(memory());

  frame.insert(new VLdui64(1, 5));
  frame.insert(new VBox(1));
  frame.insert(new VLdutf8(2, "something is amiss"));
  frame.insert(new VStageArg(1));
  frame.insert(new VCall((void*)&println));
  frame.insert(new VRet(2));
  frame.apply(renderer);
  frame.debug_print();

  void (*jit_function)() = (void (*)()) renderer.memory();
  jit_function();
}

int main2() {
  VerbajPrimitives::initialize();

  FunctionTable::add("print", (void*) &print);
  FunctionTable::add("println", (void*) &println);

  ifstream stream { "/Users/sircodesalot/Desktop/program.vbaj" };
  images::VerbajFile file(stream);

  for (auto& image : file) {
    FunctionTable::add_unbuilt_function(static_cast<images::FunctionImageLoader*>(image.get()));
  }

  void (*entry_point)() = (void(*)())FunctionTable::get("main");
  entry_point();

  return 0;
}
class MyClass {
public:
  ~MyClass() { cout << "collected" << endl; }
};