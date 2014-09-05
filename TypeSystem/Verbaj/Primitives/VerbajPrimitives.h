#include "SystemType.h"

#ifndef VARBAJ_PRIMITIVES_H
#define VARBAJ_PRIMITIVES_H

namespace verbaj {
    struct VerbajPrimitives {
        static void initialize();

        static types::SystemType vm_object;
        static types::SystemType vm_primitive;

        static types::SystemType vm_uint64;
        static types::SystemType vm_box_of_uint64;
    };
}

#endif
