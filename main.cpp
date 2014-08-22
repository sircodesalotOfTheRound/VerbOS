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

int main() {
    using namespace std;

    jit::VirtualRegisterStage<arch::OsxRegisters> stage;
    jit::VirtualRegister reg { "name", vm_string, 1 };

    stage.insert_at(3, { "thirth", vm_string, 1 });
    stage.insert_at(4, { "fourth", vm_string, 1 });
    stage.insert_at(5, reg);
    stage.insert_at(6, { "another", vm_string, 1 });

    stage.with_register(4, [](jit::ConstVirtualRegisterCheckout r) {
        cout << r.sys_register() << ", contains " << r.virtual_register() << endl;
    });

    stage.with_registers(5, 6, [](jit::ConstVirtualRegisterCheckout lhs, jit::ConstVirtualRegisterCheckout rhs) {
        cout << lhs.sys_register() << ", contains " << lhs.virtual_register() << endl;
        cout << rhs.sys_register() << ", contains " << rhs.virtual_register() << endl;
    });

    stage.with_registers(5, 6, [](jit::ConstVirtualRegisterCheckout lhs, jit::ConstVirtualRegisterCheckout rhs) {
        cout << lhs.sys_register() << ", contains " << lhs.virtual_register() << endl;
        cout << rhs.sys_register() << ", contains " << rhs.virtual_register() << endl;
    });

    stage.with_register(3, [](jit::ConstVirtualRegisterCheckout r) {
        cout << r.sys_register() << ", contains " << r.virtual_register() << endl;
    });

    return 0;
}
