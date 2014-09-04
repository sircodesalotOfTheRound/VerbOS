#include "VerbajPrimitives.h"

types::SystemType verbaj::VerbajPrimitives::vm_object { "vm.object", types::TypeFamily::CLASS };
types::SystemType verbaj::VerbajPrimitives::vm_primitive { "vm.primitive", types::TypeFamily::ABSTRACT_CLASS};

types::SystemType verbaj::VerbajPrimitives::vm_uint64 { "vm.uint64", types::TypeFamily::PRIMITIVE };

types::SystemType verbaj::VerbajPrimitives::vm_box_of_uint64 { "vm.Box<uint64>", types::TypeFamily::CLASS };

void verbaj::VerbajPrimitives::initialize() {
    vm_primitive.add_trait(vm_object);

    vm_uint64.add_trait(vm_primitive);

    vm_box_of_uint64.add_trait(vm_primitive);
    vm_box_of_uint64.add_field_definition("value", vm_uint64);

    vm_object.freeze();
    vm_primitive.freeze();
    vm_uint64.freeze();
    vm_box_of_uint64.freeze();
}
