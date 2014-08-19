#include <iostream>
#import "SystemString.h"
#import "SystemType.h"

int main() {
    using namespace std;

    SystemType my { "this is the name" };

    cout << my << endl;
    return 0;
}
