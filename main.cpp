#include <iostream>
#import "SystemString.h"
#import "SystemType.h"
#import "SystemTypeInstance.h"
#import "OsxRegisters.h"
#include "ProcessorOpCodeSet.h"
#import "ProcessorLabelOpCode.h"
#import "ProcessorReturnOpCode.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}


int main() {
    using namespace std;

    jit::JitRenderer renderer (memory());
    op::ProcessorOpCodeSet opcodes;
    opcodes.label("first");
    opcodes.mov(arch::OsxRegisters::rax, 10);
    opcodes.inc(arch::OsxRegisters::rax);
    opcodes.ret();

    opcodes.render(renderer);

    int(*pfunc)() = (int(*)())renderer.memory();

    cout << pfunc();

    return 0;
}
