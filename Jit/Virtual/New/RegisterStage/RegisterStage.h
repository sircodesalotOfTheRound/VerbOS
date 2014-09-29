//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#import "VariableInfo.h"
#include "VariableAllocator.h"

#ifndef __RegisterStage_H_
#define __RegisterStage_H_


class RegisterStage {
  const VariableAllocator& allocator_;

public:
  RegisterStage(VariableAllocator& allocator) :
    allocator_(allocator)
  {

  }

  void stage_to_register(Variable* variable) {

  }
};


#endif //__RegisterStage_H_
