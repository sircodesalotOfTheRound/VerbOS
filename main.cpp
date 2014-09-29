#include <iostream>
#include "VariableAllocator.h"
#include "VerbajPrimitives.h"

using namespace std;

int main() {
  op::ProcessorOpCodeSet jit_opcodes {};
  VariableAllocator allocator(20, jit_opcodes);

  allocator.insert(6, verbaj::VerbajPrimitives::vm_utf8, 1, false, false);
  allocator.with_variable(6, [](VariableCheckout& checkout) {
    const Variable* variable = checkout.variable();
    cout << variable->type() << endl;
  });

  allocator.persist_variables();

  allocator.with_variable(6, [](VariableCheckout& checkout){
    const Variable* variable = checkout.variable();
    cout << variable->type() << endl;
  });

}