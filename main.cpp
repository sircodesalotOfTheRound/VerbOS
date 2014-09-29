#include <iostream>
#include "VariableAllocator.h"
#include "VerbajPrimitives.h"
#include "Stackframe.h"

using namespace std;
using namespace op;

int main() {
  Stackframe frame(20);
  VariableAllocator& allocator = frame.allocator();
  ProcessorOpCodeSet& jit_opcodes = frame.jit_opcodes();

  allocator.insert(6, verbaj::VerbajPrimitives::vm_utf8, 1, false, false);
  allocator.insert(7, verbaj::VerbajPrimitives::vm_object, 1, false, false);
  allocator.insert(6, verbaj::VerbajPrimitives::vm_uint64, 1, false, false);
  allocator.with_variable(6, [](VariableCheckout& checkout) {
    const Variable* variable = checkout.variable();
    cout << variable->type() << endl;
  });

  allocator.persist_variables();

  allocator.with_variable(6, [](VariableCheckout& checkout){
    const Variable* variable = checkout.variable();
    cout << variable->type() << endl;
  });

  jit_opcodes.debug_print();

}