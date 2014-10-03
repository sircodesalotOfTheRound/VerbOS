#include <iostream>
#include "Stackframe.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VCall.h"
#include "VStageArg.h"
#include "VerbajPrimitives.h"
#include "Instance.h"
#include <unistd.h>
#include <thread>
#include <pthread.h>

using namespace std;
using namespace op;
using namespace jit;
using namespace verbaj;
using namespace types;

void stuff();
int main2();

int main() {
  stuff();
  main2();
}

