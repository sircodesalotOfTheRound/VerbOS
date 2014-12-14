
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
#import "ManagedStack.h"
#import "ExecutionEnvironment.h"
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

void simple_copy() {
  ExecutionEnvironment::initialize();

  Stackframe frame(20, 5);
  JitRenderer renderer(memory());

  frame.insert(new VLdui64(1, 5));
  frame.insert(new VCopy(5, 1));
  frame.insert(new VRet(5));

  frame.apply(renderer);
  frame.debug_print();

  ManagedThread thread(renderer.memory());
  thread.start();

  cout << thread.return_value<uint64_t>() << endl;
}

int main2() {
  ExecutionEnvironment::initialize();

  FunctionTable::add("print", (void*) &print);
  FunctionTable::add("println", (void*) &println);

  ifstream stream { "/Users/sircodesalot/Desktop/program.vbaj" };
  images::VerbajFile file(stream);

  for (auto& image : file) {
    FunctionTable::add_unbuilt_function(static_cast<images::FunctionImageLoader*>(image.get()));
  }

  ManagedThread thread (FunctionTable::get("main"));
  thread.start();

  cout << endl;
  return 0;
}
class MyClass {
public:
  ~MyClass() { cout << "collected" << endl; }
};