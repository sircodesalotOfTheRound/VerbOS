//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __SelfPointer_H_
#define __SelfPointer_H_

namespace types {
    class ObjectInstance;
    class InstanceHeadPointer {
        ObjectInstance& self_;

    public:
        InstanceHeadPointer(ObjectInstance& self) : self_(self) { }

        ObjectInstance& operator*() const { return self_; }
        ObjectInstance* operator->() const { return &self_; }
    };
}


#endif //__SelfPointer_H_
