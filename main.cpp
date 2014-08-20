#include <iostream>
#import "SystemString.h"
#import "SystemType.h"
#import "SystemTypeInstance.h"

SystemType vm_object { "vm.object", 0 };
SystemType vm_int32 { "vm.int32", 0 };
SystemType vm_string { "vm.string", 1 };

int main() {
    using namespace std;

    vm_string.add_field_definition({ "length", vm_string });
    vm_string.add_trait(vm_object);

    SystemTypeInstance an_object { vm_object };
    SystemTypeInstance an_integer { vm_int32 };
    SystemTypeInstance a_string { vm_string };

    return 0;
}
