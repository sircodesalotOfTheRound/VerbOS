#include <iostream>
#include "VariableAllocator.h"
#include "VerbajPrimitives.h"

using namespace std;

int main() {
  VariableAllocator allocator(20);

  allocator.subscribe_on_variable_inserted([](Variable* variable){
    cout << "just added: ";
    cout << variable->type() << endl;
  });

  allocator.insert(5, verbaj::VerbajPrimitives::vm_utf8, 1, false, false);
}