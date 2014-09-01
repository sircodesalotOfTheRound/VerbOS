//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __SelfPointer_H_
#define __SelfPointer_H_

namespace types {
    class Instance;
    struct InstanceSelfPointer {
        Instance* self_;

    public:
        Instance& operator*() const { return *self_; }
        Instance* operator->() const { return self_; }
    };
}


#endif //__SelfPointer_H_
