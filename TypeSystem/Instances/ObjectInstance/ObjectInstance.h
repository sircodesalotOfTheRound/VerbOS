//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __SystemTypeInstance_H_
#define __SystemTypeInstance_H_

#include <stdlib.h>
#include "TypeDef.h"
#import "SystemType.h"
#import "ObjectInstanceHeader.h"

namespace types {
    class ObjectInstance {
        ObjectInstanceHeader header_;

    public:
        ObjectInstance() { };

        void* operator new (size_t size, const SystemType& type) {
            ObjectInstance *instance = (ObjectInstance*) malloc(size);

            // Set the object type. Then zeroize the meta info.
            instance->header_.data_[0] = (uintptr_t)&type;
            instance->header_.data_[1] = 0;

            return instance;
        }

        /*const SystemType &def() const {
            // Since we may be pointing at a base stripe, we need to
            // cast to the root of the object.
            return *(SystemType *) get_root()->data_[1];
        }


        inline ObjectInstance *get_root() const {
            return (ObjectInstance *) data_[0];
        }

        bool isa(std::string name) {
            return def().isa(name);
        }*/

        SystemType& type() { return header_.type(); }

        // Dissallow movement for now.
        ObjectInstance(const ObjectInstance &) = delete;
        ObjectInstance(ObjectInstance &&) = delete;
        ObjectInstance operator=(const ObjectInstance &) = delete;
        ObjectInstance operator=(ObjectInstance &&) = delete;

    };
}


#endif //__SystemTypeInstance_H_
