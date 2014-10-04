#include <iostream>
#include "Stackframe.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VCall.h"
#include "VStageArg.h"
#include "VerbajPrimitives.h"
#include "Instance.h"
#import "MemoryAllocator.h"
#include <unistd.h>
#include <thread>
#include <pthread.h>

using namespace std;
using namespace op;
using namespace jit;
using namespace verbaj;
using namespace types;
using namespace gc;

void stuff();
int main2();
int simple_copy();

int main() {
  MemoryAllocator allocator;

  while (true) {
    cout << allocator.allocate(100) << endl;
  }
}

