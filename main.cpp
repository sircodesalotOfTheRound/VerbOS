#include <iostream>
#include "CPURegister.h"
#import "SystemString.h"

int main() {
    using namespace std;

    SystemString str { "something like that" };
    const char* pstr = str.c_str();

    return 0;
}
