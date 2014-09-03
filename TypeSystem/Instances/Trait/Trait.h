//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ClassBand_H_
#define __ClassBand_H_

#include "TypeDef.h"
#include "InstanceClassPointer.h"

namespace types {
    struct Trait {
        Instance* instance_pointer_;

    public:
        // Should be initialized on 'new'. Empty constructor.
        Trait() { }

        Trait(Instance* instance)
        {

        }

        Instance& get_instance() { return *instance_pointer_; }

        template<class T>
        T* data() { return (T*)(((uintptr_t*)this) + 1); }

        template<class T>
        T* data(off_t byte_offset) { return (T*)&((byte*)this)[byte_offset + 8]; }
    };
}

#endif //__ClassBand_H_
