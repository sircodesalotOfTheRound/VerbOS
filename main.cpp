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
    VirtualVariableStagingAllocator allocator(10);

    for (int index = 0; index != 14; ++index) {
        VirtualVariable variable(index, VerbajPrimitives::vm_object, 1, true);
        allocator.bind_to_system_register(std::move(variable));
    }

    for (int index = 0; index != 14; ++index) {
        allocator.with_register(index, [](const VirtualVariableCheckout& checkout) {
            cout << checkout.sys_register() << ": " << checkout.variable_number() << endl;
        });
    }


    return 0;
}
