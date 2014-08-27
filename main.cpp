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

    VirtualVariable variable(1, VerbajPrimitives::vm_object, 1, true);
    allocator.bind_to_system_register(std::move(variable));

    VirtualVariable variable2(2, VerbajPrimitives::vm_object, 1, true);
    allocator.bind_to_stack_persistence(std::move(variable2));



    allocator.with_register(1, [](VirtualVariableCheckout& checkout) {
        cout << checkout.sys_register() << endl;
    });

    allocator.with_register(2, [](VirtualVariableCheckout& checkout) {
        cout << checkout.sys_register() << endl;
    });

    return 0;
}
