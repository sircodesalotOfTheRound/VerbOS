#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#import "VirtualStackFrameRegisterSet.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;

int main() {
    JitRenderer renderer { memory() };
    VirtualStackFrame stack_frame;

    stack_frame.add_op(new VLdui64(1, 42));
    stack_frame.add_op(new VLdui64(2, 69));
    stack_frame.add_op(new VRet(2));

    stack_frame.apply(renderer);


    uint64_t (*pfunc)() = (uint64_t(*)())renderer.memory();

    cout << pfunc() << endl;
    return 0;
}
