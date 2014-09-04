#include "VerbajPrimitives.h"

const types::SystemType verbaj::VerbajPrimitives::vm_uint64 { "vm.uint64", types::TypeFamily::PRIMITIVE };

const types::SystemType verbaj::VerbajPrimitives::vm_object { "vm.object", types::TypeFamily::CLASS };
const types::SystemType verbaj::VerbajPrimitives::vm_box_of_uint64 { "vm.Box<uint64>", types::TypeFamily::CLASS };
