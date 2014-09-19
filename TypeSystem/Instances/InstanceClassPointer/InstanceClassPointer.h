//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __SelfPointer_H_
#define __SelfPointer_H_

namespace types {
  class Instance;

  struct InstanceClassPointer {
    Instance* self_;

  public:
    Instance& operator*() const;
    Instance* operator->() const;
  };
}


#endif //__SelfPointer_H_
