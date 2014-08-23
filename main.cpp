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
    op::ProcessorOpCodeSet opcodes { };

    auto rax = arch::OsxRegisters::rax;
    auto rbx = arch::OsxRegisters::rbx;

    opcodes.mov(rax, 15);
    opcodes.mov(rbx, 25);
    opcodes.push(rax);
    opcodes.push(rbx);
    opcodes.pop(rax);
    opcodes.pop(rbx);
    opcodes.ret();

    opcodes.render(renderer);

    int(*pfunc)() = (int(*)())renderer.memory();

    cout << pfunc();

    return 0;
}
