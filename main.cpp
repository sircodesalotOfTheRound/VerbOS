#include <iostream>
#include "VariableAllocator.h"
#include "VerbajPrimitives.h"

using namespace std;

int main() {
  VariableAllocator allocator(20);

  allocator.insert(5, verbaj::VerbajPrimitives::vm_utf8, 1, false, false);
  allocator.with_variable(5, [](Variable* variable) {

  });
}