//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __StackPersistStage_H_
#define __StackPersistStage_H_

#include "VariableContainer.h"

class StackPersistStage {
  const VariableContainer& container_;

public:
  StackPersistStage(VariableContainer& container): container_(container) { }
};


#endif //__StackPersistStage_H_
