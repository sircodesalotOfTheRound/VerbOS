#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VerbajPrimitives.h"
#include "VRet.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;

uint64_t add_together(uint64_t lhs, uint64_t rhs) {
    return lhs + rhs;
}

int main() {
    JitRenderer renderer(memory());
    VirtualStackFrame frame(20);

    frame.insert(new VLdui64(1, 69));
    frame.insert(new VLdui64(2, 42));
    frame.insert(new VRet(2));

    frame.apply(renderer);

    uint64_t(*pfunc)() = (uint64_t(*)())renderer.memory();

    cout << pfunc() << endl;


    return 0;
}
