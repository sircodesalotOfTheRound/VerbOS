#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#import "VirtualStackFrameRegisterSet.h"
#import "ObjectInstanceHeader.h"
#include "VerbajPrimitives.h"
#import "ObjectInstance.h"
#import "VirtualRegisterBindingTable.h"
#include "VCall.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;

uint64_t my_function(int value) {
    cout << "working so far: " << value << endl;

    return 10;
}

int main() {
    JitRenderer renderer(memory());
    VirtualStackFrame frame;

    frame.insert(new VLdui64(9, 9));
    frame.insert(new VLdui64(10, 10));
    frame.insert(new VCall(&my_function));
    frame.insert(new VRet(3));

    frame.apply(renderer);
    frame.debug_print();

    renderer.debug_print();


    uint64_t(*pfunc)() = (uint64_t(*)())renderer.memory();

    cout << pfunc() << endl;

    return 0;
}
