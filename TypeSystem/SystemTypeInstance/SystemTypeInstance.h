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

    const SystemType& def() const {
        // Since we may be pointing at a base stripe, we need to
        // cast to the root of the object.
        return *(SystemType*)get_root()->data_[1];
    }


    inline SystemTypeInstance* get_root() const {
        return (SystemTypeInstance *) data_[0];
    }

    bool isa(std::string name) {
        return def().isa(name);
    }


    // Dissallow movement for now.
    SystemTypeInstance(const SystemTypeInstance&) = delete;
    SystemTypeInstance(SystemTypeInstance&&) = delete;
    SystemTypeInstance operator=(const SystemTypeInstance&) = delete;
    SystemTypeInstance operator=(SystemTypeInstance&&) = delete;

    ~SystemTypeInstance() { delete[] data_; }
};


#endif //__SystemTypeInstance_H_
