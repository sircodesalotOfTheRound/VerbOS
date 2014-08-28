#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VerbajPrimitives.h"
#include "VRet.h"
#include "VCall.h"
#include "VStageArg.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;

void add_together(uint64_t lhs, uint64_t rhs) {
    cout << lhs << " + " << rhs << " = " << (lhs + rhs) << endl;
}

int main() {
    JitRenderer renderer(memory());
    VirtualStackFrame frame(20);

    frame.insert(new VLdui64(1, 69));
    frame.insert(new VLdui64(2, 42));
    frame.insert(new VLdui64(3, 32));
    frame.insert(new VLdui64(4, 100));
    frame.insert(new VStageArg(3));
    frame.insert(new VStageArg(4));
    frame.insert(new VCall(&add_together));
    frame.insert(new VRet(2));

    frame.apply(renderer);

    uint64_t(*pfunc)() = (uint64_t(*)())renderer.memory();

    pfunc();
    frame.debug_print();

    return 0;
}
