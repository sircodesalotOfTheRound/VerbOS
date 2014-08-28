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

    for (int index = 0; index != 10; ++index) {
        VirtualVariable variable(index, VerbajPrimitives::vm_object, 1, true);
        allocator.stack_persist(std::move(variable));
    }

    //VirtualVariable variable(2, VerbajPrimitives::vm_object, 1, true);

    for (int index = 0; index != 10; ++index) {
        allocator.with_register(index, [](const VirtualVariableCheckout& checkout) {
            cout << checkout.variable_number() << ": " << checkout.sys_register() << endl;
        });
    }

    //allocator.stack_persist(std::move(variable));
    allocator.bind_to_system_register(OsxRegisters::rsi, 2);

    cout << std::endl;
    allocator.show();


    return 0;
}
