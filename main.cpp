#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VStageArg.h"
#include "Functions.h"
#include "VCall.h"
#include "Instance.h"
#include "VerbajPrimitives.h"
#import "VBox.h"
#include "ContainerIterator.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t) getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;
using namespace types;

void print_value(uint64_t lhs, uint64_t rhs) {
    cout << lhs << " + " << rhs << " = " << (lhs + rhs) << endl;
}

void stuff() {

    VirtualStackFrame frame(20);
    JitRenderer renderer(memory());

    frame.insert(new VLdui64(1, 5));
    frame.insert(new VBox(1));
    frame.insert(new VRet(1));
    frame.apply(renderer);
    frame.debug_print();

    Trait* (* pfunc)() = (Trait*(*)()) renderer.memory();
    Trait* box = pfunc();

    cout << box << endl;
    cout << "boxed value: " << box->data<uint64_t>()[0] << endl;

}

int main() {
    VerbajPrimitives::initialize();
    stuff();

}

