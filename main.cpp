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
    op::ProcessorOpCodeSet opcodes { };

    VirtualRegisterStage stage { 0, opcodes };

    VLdui64 ldui64(1, 100);
    ldui64.render(stage);

    cout << stage[1] << endl;


    return 0;
}
