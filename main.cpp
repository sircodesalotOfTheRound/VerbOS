#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#import "VirtualStackFrameRegisterSet.h"
#import "ObjectInstanceHeader.h"
#include "VerbajPrimitives.h"
#import "ObjectInstance.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;

int main() {
    auto& object = verbaj::VerbajPrimitives::vm_object;

    auto header = new (object) types::ObjectInstance;
    cout << header->type() << endl;
    //cout << header->type() << endl;

    return 0;
}
