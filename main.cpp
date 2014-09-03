#include <iostream>
#include "ProcessorOpCodeSet.h"
#include "VLdui64.h"
#include "VRet.h"
#include "VStageArg.h"
#include "Functions.h"
#include "VCall.h"
#include "Instance.h"
#include "VerbajPrimitives.h"

#include <unistd.h>
#include <sys/mman.h>

void* memory() {
    return mmap(nullptr, (size_t)getpagesize(), PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

using namespace jit;
using namespace std;
using namespace verbaj;
using namespace arch;
using namespace types;

void constructor(Instance* instance) {
}

int main() {
    Instance* instance = new (VerbajPrimitives::vm_box_of_uint64) Instance(constructor);

    cout << instance->type() << endl;
    instance->head().data<uint64_t>()[0] = 22;
    Trait* ptrait = &instance->head();

    uint64_t storage = 0;

    __asm {
        mov rsi, [ptrait]
        add rsi, 8

        lea rdi, storage
        mov rsi, [rsi]
        mov [rdi], rsi
    }

    cout << storage << endl;
}

