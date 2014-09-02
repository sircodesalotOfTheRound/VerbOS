//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __SystemTypeInstance_H_
#define __SystemTypeInstance_H_

#include <stdlib.h>
#include "TypeDef.h"
#import "SystemType.h"
#import "InstanceHeader.h"
#import "InstanceClassPointer.h"
#import "Trait.h"

namespace types {
    class Instance {
        InstanceHeader header_;
        Trait head_trait;

    public:
        Instance() { };

        void* operator new (size_t size, const SystemType& type) {
            // Todo: change size to instead use the size derived from the type.
            Instance*instance = (Instance*)malloc(size);

            // Set the object type. Then zeroize the meta info.
            instance->header_.data_[0] = (uintptr_t)&type;
            instance->header_.data_[1] = 0;

            // Initialize the head class band. (Dangerous manual initialization).
            instance->header_.data_[2] = (uintptr_t)&*instance;

            return instance;
        }

        Trait* head_class_band() { return &head_trait; }

        SystemType& type() { return header_.type(); }

        // Dissallow movement for now.
        Instance(const Instance&) = delete;
        Instance(Instance&&) = delete;
        Instance operator=(const Instance&) = delete;
        Instance operator=(Instance&&) = delete;

    };
}


#endif //__SystemTypeInstance_H_
