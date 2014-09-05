//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "SystemType.h"
#include "Trait.h"

const types::SystemType& types::SystemType::NONE = SystemType("<NONE>", types::TypeFamily::PRIMITIVE, types::TypeFlags::PUBLIC);

void types::SystemType::freeze() const {
    // If the type is already frozen, return.
    if (is_frozen()) {
        return;
    }

    // Todo: should ensure all dependent types (traits, subclasses, field types) are also
    // frozen (since the size of this type is dependent on the size of the others.
    is_frozen_ = true;

    // Todo: correct this calculation;
    size_t size_required_for_traits = 0;

    for (auto trait_iter : trait_definitions_) {
        auto& trait = trait_iter.second;

        trait->freeze();

        // Only add a trait band if the trait has specific data associated with it.
        if (trait->has_fields()) {
            // Add the size of the trait (the 'self' pointer)
            size_required_for_traits += trait->required_size() + sizeof(Trait);
        }
    }

    size_t size_required_for_fields = (sizeof(uintptr_t) * field_count_);

    required_size_ = size_required_for_fields + size_required_for_traits;
}