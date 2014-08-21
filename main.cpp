#include <iostream>
#import "SystemString.h"
#import "SystemType.h"
#import "SystemTypeInstance.h"
#import "OsxRegisters.h"
#include "ProcessorOpCodeSet.h"
#import "ProcessorLabelOpCode.h"
#import "ProcessorReturnOpCode.h"
#include "VirtualRegister.h"
#import "VirtualRegisterAllocation.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

SystemType vm_string { "vm_string", 0, 0 };

int main() {
    using namespace std;

    auto rax = arch::OsxRegisters::rax;
    jit::VirtualRegisterAllocation allocation { rax };
    jit::VirtualRegister reg { "name", vm_string, 1 };

    allocation.bind_virtual_register(reg);

    cout << allocation.virtual_register() << endl;

    return 0;
}
