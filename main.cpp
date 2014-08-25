#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#import "VirtualStackFrameRegisterSet.h"
#import "ObjectInstanceHeader.h"
#include "VerbajPrimitives.h"
#import "ObjectInstance.h"
#import "VirtualRegisterBindingTable.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;

int main() {
    VirtualRegisterBindingTable table;

    auto rax = arch::OsxRegisters::rax;
    auto r8 = arch::OsxRegisters::r8;

    VirtualRegisterBinding binding (arch::OsxRegisters::rax);
    VirtualRegister v_reg ("my_reg", verbaj::VerbajPrimitives::vm_object, VirtualRegister::Priority(1), false);
    binding.bind(5, v_reg);

    table.insert_binding(binding);


    table.remove_binding(rax);

    cout << table.is_bound(1) << endl;
    cout << table.is_bound(5) << endl;
    cout << table.is_bound(rax) << endl;
    cout << table.is_bound(r8) << endl;


    //cout << table[rax].bound_register_number() << endl;

    return 0;
}
