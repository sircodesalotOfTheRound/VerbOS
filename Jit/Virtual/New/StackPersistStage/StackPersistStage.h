//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include "VariableAllocator.h"

#ifndef __StackPersistStage_H_
#define __StackPersistStage_H_


class StackPersistStage {
  const VariableAllocator& allocator_;

public:
  StackPersistStage(VariableAllocator& allocator): allocator_(allocator) { }
};


#endif //__StackPersistStage_H_
