#include "VerbajPrimitives.h"

using namespace types;
SystemType verbaj::VerbajPrimitives::vm_object {"object", TypeFamily::CLASS, TypeFlags::PUBLIC};
SystemType verbaj::VerbajPrimitives::vm_primitive {"vm.primitive", TypeFamily::ABSTRACT_CLASS, TypeFlags::PUBLIC};

SystemType verbaj::VerbajPrimitives::vm_uint64 {"uint64", types::TypeFamily::PRIMITIVE, TypeFlags::PUBLIC};

SystemType verbaj::VerbajPrimitives::vm_utf8 {"utf8", types::TypeFamily::PRIMITIVE, TypeFlags::PUBLIC};

SystemType verbaj::VerbajPrimitives::vm_box_of_uint64{"vm.Box<uint64>", types::TypeFamily::CLASS, TypeFlags::PUBLIC};

void verbaj::VerbajPrimitives::initialize() {
  vm_object.freeze();

  vm_primitive.add_trait(vm_object);
  vm_primitive.freeze();

  vm_uint64.add_trait(vm_primitive);
  vm_uint64.freeze();

  vm_utf8.add_trait(vm_primitive);
  vm_utf8.add_field_definition("length", vm_uint64, TypeFlags::PUBLIC);
  vm_utf8.add_field_definition("string_num", vm_uint64, TypeFlags::PUBLIC);
  vm_utf8.freeze();

  vm_box_of_uint64.add_trait(vm_primitive);
  vm_box_of_uint64.add_field_definition("value", vm_uint64, TypeFlags::PRIVATE);
  vm_box_of_uint64.freeze();

}
