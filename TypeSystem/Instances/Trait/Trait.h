//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <sys/_types/_uintptr_t.h>
#include "InstanceClassPointer.h"

#ifndef __ClassBand_H_
#define __ClassBand_H_

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
    };
}

#endif //__ClassBand_H_
