#include <iostream>
#include "Stackframe.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VCall.h"
#include "VStageArg.h"
#include "VerbajPrimitives.h"
#include "Instance.h"

using namespace std;
using namespace op;
using namespace jit;
using namespace verbaj;
using namespace types;

void stuff();
int main2();
void* memory();

int main() {
  main2();
  stuff();
}
