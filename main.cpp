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
    opcodes.add(new op::ProcessorLabelOpCode("something"));
    opcodes.add(new op::ProcessorLabelOpCode("another_thing"));
    opcodes.add(new op::ProcessorReturnOpCode());

    opcodes.render(renderer);

    void(*pfunc)() = (void(*)())renderer.memory();

    pfunc();

    auto rax = arch::OsxRegisters::rax;

    cout << *rax << endl;
    cout << rax[10] << endl;

    return 0;
}
