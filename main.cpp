#include <iostream>
#import "SystemString.h"
#import "SystemType.h"
#import "SystemTypeInstance.h"

SystemType vm_object { "vm.object" };
SystemType vm_int32 { "vm.int32" };

int main() {
    using namespace std;

    SystemTypeInstance an_object { vm_object };
    SystemTypeInstance an_integer { vm_int32 };

    cout << an_object.def() << endl;
    cout << an_integer.def() << endl;

    return 0;
}
