//
// Created by Reuben Kuhnert on 14/9/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ObjectImage_H_
#define __ObjectImage_H_

#include <string>
#include "TypeDef.h"

namespace images {
  class ObjectImage {
  public:
    virtual std::string image_name() const = 0;
  };
}

#endif //__ObjectImage_H_
