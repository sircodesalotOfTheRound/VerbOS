//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __SystemTypeInstance_H_
#define __SystemTypeInstance_H_

#include <stdlib.h>
#include "TypeDef.h"
#import "SystemType.h"

class SystemTypeInstance {
    uintptr_t* data_;

public:
    SystemTypeInstance(const SystemType& type) {
        data_ = new uintptr_t[2];

        data_[0] = (uintptr_t)this;
        data_[1] = (uintptr_t)&type;
    }

    const SystemType& def() {
        // Since we may be pointing at a base stripe, we need to
        // cast to the root of the object.
        SystemTypeInstance* root_ptr = (SystemTypeInstance *) data_[0];
        return *(SystemType*)root_ptr->data_[1];
    }

    // Dissallow movement for now.
    SystemTypeInstance(const SystemTypeInstance&) = delete;
    SystemTypeInstance(SystemTypeInstance&&) = delete;
    SystemTypeInstance operator=(const SystemTypeInstance&) = delete;
    SystemTypeInstance operator=(SystemTypeInstance&&) = delete;

    ~SystemTypeInstance() { delete[] data_; }
};


#endif //__SystemTypeInstance_H_
