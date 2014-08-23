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

int main() {
    JitRenderer renderer(memory());

    StackFrame frame;
    frame.add_op(new VLdui64(1, 69));
    frame.add_op(new VLdui64(2, 42));
    frame.add_op(new VLdui64(3, 56));
    frame.add_op(new VRet(3));

    frame.apply(renderer);

    frame.debug_print();

    uint64_t (*pfunc)() = (uint64_t(*)())renderer.memory();

    cout << pfunc() << endl;

    return 0;
}
