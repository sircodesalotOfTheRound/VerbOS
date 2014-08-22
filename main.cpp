#include <iostream>
#import "SystemString.h"
#import "SystemType.h"
#import "SystemTypeInstance.h"
#import "OsxRegisters.h"
#include "ProcessorOpCodeSet.h"
#import "ProcessorLabelOpCode.h"
#import "ProcessorReturnOpCode.h"
#include "VirtualRegister.h"
#import "VirtualRegisterBinding.h"
#include "VirtualRegisterStage.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

SystemType vm_string { "vm_string", 0, 0 };
SystemType vm_object { "vm_object", 0, 0 };

#include <sstream>

int main() {
    using namespace jit;
    using namespace std;

    jit::JitRenderer renderer(memory());
    op::ProcessorOpCodeSet op_codes;

    jit::VirtualRegisterStage stage(3);
    jit::VirtualRegister reg { "name", vm_string, VirtualRegister::Priority(1), VirtualRegister::Offset(0) };

    stage.insert_at(0, { "first", vm_object, VirtualRegister::Priority(1), VirtualRegister::Offset(1) });
    stage.insert_at(1, { "second", vm_object, VirtualRegister::Priority(1), VirtualRegister::Offset(2) });

    stage.with_registers(0, 1, [](jit::ConstVirtualRegisterCheckout lhs, jit::ConstVirtualRegisterCheckout rhs) {
        cout << lhs.sys_register() << ", contains " << lhs.virtual_register() << endl;
        cout << rhs.sys_register() << ", contains " << rhs.virtual_register() << endl;
    });

    return 0;
}
