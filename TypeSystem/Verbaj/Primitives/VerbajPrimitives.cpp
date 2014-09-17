#include "VerbajPrimitives.h"

using namespace types;
SystemType verbaj::VerbajPrimitives::vm_object { "vm.object", TypeFamily::CLASS, TypeFlags::PUBLIC };
SystemType verbaj::VerbajPrimitives::vm_primitive { "vm.primitive", TypeFamily::ABSTRACT_CLASS, TypeFlags::PUBLIC };

SystemType verbaj::VerbajPrimitives::vm_uint64 { "vm.uint64", types::TypeFamily::PRIMITIVE, TypeFlags::PUBLIC};

SystemType verbaj::VerbajPrimitives::vm_box_of_uint64 { "vm.Box<uint64>", types::TypeFamily::CLASS, TypeFlags::PUBLIC};

void verbaj::VerbajPrimitives::initialize() {
    vm_primitive.add_trait(vm_object);

    vm_uint64.add_trait(vm_primitive);

    vm_box_of_uint64.add_trait(vm_primitive);
    vm_box_of_uint64.add_field_definition("<*>value", vm_uint64, TypeFlags::PRIVATE);

    vm_object.freeze();
    vm_primitive.freeze();
    vm_uint64.freeze();
    vm_box_of_uint64.freeze();

    std::cout << vm_object.required_size() << std::endl;
}
