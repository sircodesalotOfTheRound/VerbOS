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

    VLdui64 ldui641(1, 5);
    VLdui64 ldui642(2, 6);
    VLdui64 ldui643(3, 7);
    VLdui64 ldui644(4, 8);

    ldui641.apply(stage);
    ldui642.apply(stage);
    ldui643.apply(stage);
    ldui644.apply(stage);

    cout << stage[1] << endl;

    opcodes.ret();
    opcodes.render(renderer);

    for (auto& opcode : opcodes) {
        cout << *opcode << endl;
    }

    uint64_t (*pfunc)() = (uint64_t(*)())renderer.memory();

    cout << pfunc() << endl;

    return 0;
}
