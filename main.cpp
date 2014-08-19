#include <iostream>
#include "CPURegister.h"
#import "SystemString.h"

int main() {
    using namespace std;

    SystemString str { "something like that" };
    cout << str.length() << endl;
    cout << str << endl;

    return 0;
}
