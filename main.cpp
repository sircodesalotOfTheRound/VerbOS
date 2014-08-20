#include <iostream>
#import "SystemString.h"
#import "SystemType.h"
#import "SystemTypeInstance.h"
#import "OsxRegisters.h"


int main() {
    using namespace std;

    arch::OsxRegisters osx_registers;
    auto rax = osx_registers.rax;

    cout << rax << endl;

    return 0;
}
