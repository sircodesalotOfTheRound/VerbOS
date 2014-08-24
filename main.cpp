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
    op::ProcessorOpCodeSet set { };

    auto rax = arch::OsxRegisters::rax;
    auto r8 = arch::OsxRegisters::rbx;

    set.mov(rax, 10);
    set.mov(r8, 5);
    set.sub(rax, r8);

    set.ret();

    set.render(renderer);

    uint64_t (*pfunc)() = (uint64_t(*)())renderer.memory();

    cout << dec << pfunc() << endl;

    return 0;
}
