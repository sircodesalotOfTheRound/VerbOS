//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "InstanceClassPointer.h"

#ifndef __ClassBand_H_
#define __ClassBand_H_

namespace types {
    struct Trait {
        InstanceClassPointer instance_pointer_;

    public:
        Trait()
        {

        }

        Instance& get_instance() { return *instance_pointer_; }
    };
}

#endif //__ClassBand_H_
