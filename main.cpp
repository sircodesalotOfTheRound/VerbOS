#include <iostream>
#include "CPURegister.h"

int main() {
    using namespace std;

    processor::CPURegister reg ("rax", 0x00, 64, false);
    cout << reg << endl;

    return 0;
}
