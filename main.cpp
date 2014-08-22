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

SystemType vm_uint64 { "vm_uint64", 0, 0 };

#include <sstream>

using namespace jit;
using namespace std;
void add(jit::VirtualRegisterStage& stage, int l_reg, int r_reg) {
    stage.with_registers(0, 1, [](jit::ConstVirtualRegisterCheckout lhs, jit::ConstVirtualRegisterCheckout rhs) {
        cout << lhs.virtual_register() << endl;
        cout << rhs.virtual_register() << endl;
    });
}

int main() {
    jit::JitRenderer renderer(memory());
    op::ProcessorOpCodeSet op_codes { };

    jit::VirtualRegisterStage stage { 3, op_codes };
    jit::VirtualRegister reg { "name", vm_uint64, VirtualRegister::Priority(1), VirtualRegister::Offset(0) };

    stage.insert_at(0, { "left_hand_side", vm_uint64, VirtualRegister::Priority(1), VirtualRegister::Offset(1) });
    stage.insert_at(1, { "right_hand_side", vm_uint64, VirtualRegister::Priority(1), VirtualRegister::Offset(2) });

    add(stage, 0, 1);

    return 0;
}
