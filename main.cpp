#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
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
    VirtualStackFrame frame;

    frame.insert(new VLdui64(1, 1));
    frame.insert(new VLdui64(2, 2));
    frame.insert(new VLdui64(3, 3));
    frame.insert(new VLdui64(4, 4));
    frame.insert(new VLdui64(5, 5));
    frame.insert(new VLdui64(6, 6));
    frame.insert(new VLdui64(7, 7));
    frame.insert(new VLdui64(8, 8));
    frame.insert(new VLdui64(9, 9));
    frame.insert(new VLdui64(10, 10));
    frame.insert(new VLdui64(11, 11));
    frame.insert(new VLdui64(12, 12));
    frame.insert(new VLdui64(13, 13));
    frame.insert(new VLdui64(14, 14));
    frame.insert(new VLdui64(15, 15));
    frame.insert(new VLdui64(16, 16));
    frame.insert(new VLdui64(17, 17));
    frame.insert(new VRet(15));

    frame.apply(renderer);
    frame.debug_print();

    renderer.debug_print();


    uint64_t(*pfunc)() = (uint64_t(*)())renderer.memory();

    cout << pfunc() << endl;

    return 0;
}
