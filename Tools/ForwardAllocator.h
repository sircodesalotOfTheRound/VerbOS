//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ForwardAllocator_H_
#define __ForwardAllocator_H_

#include <cstddef>
#include <stdlib.h>

namespace tools {
    template<class T>
    class ForwardAllocator {
    public:
        T* allocate(size_t size) { return (T*)malloc(sizeof(T) * size); }

    private:
        void deallocate(size_t size, T* pointer) { }
    };
}


#endif //__ForwardAllocator_H_
