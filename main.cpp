#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VStageArg.h"
#include "VirtualVariableStackPersistenceStage.h"
#include "VerbajPrimitives.h"
#include "VirtualVariableSystemRegisterStage.h"

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
    SystemRegisterPriorityQueue queue;
    VirtualVariableSystemRegisterBinding binding(0, OsxRegisters::rax);

    queue.insert_system_register_binding(VirtualVariableSystemRegisterBinding(0, OsxRegisters::rax));
    queue.insert_system_register_binding(VirtualVariableSystemRegisterBinding(1, OsxRegisters::rbx));
    queue.insert_system_register_binding(VirtualVariableSystemRegisterBinding(2, OsxRegisters::rcx));
    queue.insert_system_register_binding(VirtualVariableSystemRegisterBinding(3, OsxRegisters::rdx));

    VirtualVariable variable (3, VerbajPrimitives::vm_object, 1, true);

    queue.bind(arch::OsxRegisters::rdx, std::move(variable));

    cout << queue.is_bound(1);
    cout << queue.is_bound(2);
    cout << queue.is_bound(3);


    cout << queue.unbind(3).type() << endl;


    return 0;
}
