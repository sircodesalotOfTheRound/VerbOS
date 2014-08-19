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

    SystemTypeInstance an_object { vm_object };
    SystemTypeInstance an_integer { vm_int32 };
    SystemTypeInstance a_string { vm_string };

    cout << an_object.def() << endl;
    cout << an_integer.def().field_count() << endl;
    cout << a_string.def().field_count() << endl;

    return 0;
}
