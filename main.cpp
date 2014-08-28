#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VStageArg.h"
#include "VirtualVariableStackPersistenceStage.h"
#include "VerbajPrimitives.h"
#include "VirtualVariableSystemRegisterStage.h"
#import "VirtualVariableStagingAllocator.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;

uint64_t add_together(uint64_t lhs, uint64_t rhs) {
    return lhs + rhs;
}

int main() {
    VirtualVariableStagingAllocator allocator(20);

    for (int index = 0; index != 16; ++index) {
        VirtualVariable variable(index, VerbajPrimitives::vm_object, 1, true);
        allocator.bind_to_system_register(std::move(variable));
    }

    allocator.show();


    return 0;
}
