//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "SystemType.h"
#include "InstanceHeader.h"
#include "Trait.h"

const types::SystemType& types::SystemType::NONE = SystemType("<NONE>", types::TypeFamily::PRIMITIVE, types::TypeFlags::PUBLIC);

void types::SystemType::freeze() {
    if (is_frozen()) {
        throw std::logic_error("type is already frozen");
    }

    // Todo: should ensure all dependent types (traits, subclasses, field types) are also
    // frozen (since the size of this type is dependent on the size of the others.
    is_frozen_ = true;

    // Todo: correct this calculation;
    size_t size_required_for_header = (sizeof(InstanceHeader));
    size_t size_required_for_traits = (sizeof(Trait) * trait_count_);
    size_t size_required_for_fields = (sizeof(uintptr_t) * field_count_);

    required_size_ = (size_required_for_header
        + size_required_for_fields
        + size_required_for_traits);
}