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
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;
using namespace types;

void print_value(uint64_t lhs, uint64_t rhs) {
    cout << lhs << " + " << rhs << " = " << (lhs + rhs) << endl;
}

int main() {
    VirtualStackFrame frame(20);
    JitRenderer renderer (memory());

    for (int index = 0; index != 20; ++index) {
        frame.insert(new VLdui64(index, index));
    }

    frame.insert(new VStageArg(11));
    frame.insert(new VStageArg(4));
    frame.insert(new VCall(&print_value));
    frame.insert(new VRet(1));
    frame.apply(renderer);

    int (*pfunc)() = (int(*)())renderer.memory();
    cout << pfunc() << endl;

}

