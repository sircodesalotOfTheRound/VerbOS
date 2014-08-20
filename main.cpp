#include <iostream>
#import "SystemString.h"
#import "SystemType.h"
#import "SystemTypeInstance.h"
#import "OsxRegisters.h"
#include "ProcessorOpCodeSet.h"
#import "ProcessorLabelOpCode.h"
#import "ProcessorReturnOpCode.h"


int main() {
    using namespace std;

    op::ProcessorOpCodeSet opcodes;
    opcodes.add(new op::ProcessorLabelOpCode("something"));
    opcodes.add(new op::ProcessorLabelOpCode("another_thing"));
    opcodes.add(new op::ProcessorReturnOpCode());

    for (auto& opcode : opcodes) {
        cout << *opcode << endl;
    }


    return 0;
}
