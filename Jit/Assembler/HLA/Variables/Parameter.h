//
// Created by Reuben Kuhnert on 14/8/3.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "Variable.h"

#ifndef __Parameter_H_
#define __Parameter_H_


namespace hla {
    class Parameter : public Variable {
        Parameter(std::string name, const typesys::VerbosType& type, sysarch::RegisterAllocator& allocator, off_t mem_offset)
            : Variable(name, type, allocator, mem_offset) {

        }
    };
}


#endif //__Parameter_H_
