//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "InstanceHeadPointer.h"

#ifndef __ClassBand_H_
#define __ClassBand_H_

namespace types {
    class ClassBand {
        InstanceHeadPointer instance_pointer_;

    public:
        ClassBand(ObjectInstance& instance) :
            instance_pointer_(instance)
        {

        }

        ObjectInstance& get_instance() { return *instance_pointer_; }
    };
}

#endif //__ClassBand_H_
