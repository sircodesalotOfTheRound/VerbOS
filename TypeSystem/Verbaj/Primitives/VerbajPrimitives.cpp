#include "VerbajPrimitives.h"

const SystemType verbaj::VerbajPrimitives::vm_uint64 { "vm.uint64", 0, 0, 0, false };

const SystemType verbaj::VerbajPrimitives::vm_object { "vm.object", 0, 0, 0, true };
const SystemType verbaj::VerbajPrimitives::vm_box_of_uint64 { "vm.Box<uint64>", 0, 0, 8, true };
