#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#import "VirtualStackFrameRegisterSet.h"
#import "ObjectInstanceHeader.h"
#include "VerbajPrimitives.h"
#import "ObjectInstance.h"
#import "VirtualRegisterBindingTable.h"

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
    frame.insert(new VRet(10));
    frame.apply(renderer);

    frame.debug_print();

    uint64_t(*pfunc)() = (uint64_t(*)())renderer.memory();
    cout << pfunc() << endl;

    return 0;
}
