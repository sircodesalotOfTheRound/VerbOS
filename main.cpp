#include <iostream>
#include "Stackframe.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VCall.h"
#include "VStageArg.h"

using namespace std;
using namespace op;
using namespace jit;
using namespace verbaj;

void* memory();

void something(uint64_t value) {
  cout << value << endl;
  cout << "something" << endl;
}

int main() {
  jit::JitRenderer renderer (memory());
  op::ProcessorOpCodeSet jit_opcodes { };

  Stackframe frame(20, 2);
  frame.insert(new VLdui64(1, 100));
  frame.insert(new VLdui64(2, 200));
  frame.insert(new VStageArg(2));
  frame.insert(new VCall((void*)&something));
  frame.insert(new VRet(1));

  frame.apply(renderer);
  frame.debug_print();

  jit_opcodes.render(renderer);
  jit_opcodes.debug_print();
  renderer.debug_print();

  uint64_t(*pfunc)() = (uint64_t(*)())renderer.memory();

  cout << pfunc() << endl;

}
