#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VStageArg.h"
#include "Functions.h"
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

void add_together(uint64_t lhs, uint64_t rhs) {
    cout << lhs << " + " << rhs << " = " << (lhs + rhs) << endl;
}

void leave(uint64_t arg, uint64_t rhs) {
    exit(static_cast<int>(rhs));
}

int main() {
    JitRenderer renderer(memory());
    VirtualStackFrame frame(20);

    for (int index = 0; index != 20; ++index) {
        frame.insert(new VLdui64(index, index));
    }

    frame.insert(new VStageArg(2));
    frame.insert(new VStageArg(15));
    frame.insert(new VCall(&add_together));
    frame.insert(new VRet(13));

    frame.apply(renderer);

    uint64_t(*pfunc)() = (uint64_t(*)())renderer.memory();

    frame.debug_print();
    renderer.debug_print();

    helpers::stack_aligned_call([&] {
        cout << pfunc() << endl;
    });

    return 0;
}
