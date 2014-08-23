#include <iostream>
#import "SystemString.h"
#import "SystemType.h"
#import "SystemTypeInstance.h"
#import "OsxRegisters.h"
#include "ProcessorOpCodeSet.h"
#import "ProcessorLabelOpCode.h"
#import "ProcessorReturnOpCode.h"
#include "VirtualRegister.h"
#import "VirtualRegisterBinding.h"
#include "VirtualRegisterStage.h"
#include "VerbajPrimitives.h"
#include "VLdui64.h"
#import "StackFrame.h"
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
    frame.add_op(new VRet(1));

    frame.apply(renderer);

    uint64_t (*pfunc)() = (uint64_t(*)())renderer.memory();

    cout << pfunc() << endl;

    return 0;
}
