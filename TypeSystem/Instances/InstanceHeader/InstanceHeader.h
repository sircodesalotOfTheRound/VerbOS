//
// Created by Reuben Kuhnert on 14/8/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ObjectInstanceHeader_H_
#define __ObjectInstanceHeader_H_

#include "TypeDef.h"
#include "SystemType.h"
#include "Instance.h"
#import "GarbageCollectionHeader.h"

namespace types {
    struct InstanceHeader {
        // 0 - 8 : System Type
        // 9 - 16 : Garbage Collection Meta
        const SystemType* type_;
        GarbageCollectionHeader gc_header_;

        InstanceHeader() { }

        InstanceHeader(const SystemType& type) : type_(&type) { }

        const SystemType& type() const { return *type_; }
        GarbageCollectionHeader& gc_header() { return gc_header_; }
    };
}


#endif //__ObjectInstanceHeader_H_
