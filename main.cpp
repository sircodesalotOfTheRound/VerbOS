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

int main() {
    Instance*instance = new (VerbajPrimitives::vm_uint64) Instance();

    cout << instance->type() << endl;
    Trait* pBand = instance->head_class_band();

    cout << pBand->get_instance().type() << endl;

}

