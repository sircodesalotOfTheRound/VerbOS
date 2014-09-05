//
// Created by Reuben Kuhnert on 14/9/4.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
// Wrote this so that you don't have to publicly expose a
// container when you really just want to iterate through the contents.
//


#ifndef __ContainerIterator_H_
#define __ContainerIterator_H_

#include "TypeDef.h"

namespace helpers {
    template<class T>
    class ContainerIterator {
        using iterator = typename T::iterator;
        const T& container_;

    public:
        ContainerIterator(T& container) : container_(container) { }

        decltype(container_.begin()) begin() { return container_.begin(); }
        decltype(container_.end()) end() { return container_.end(); }
    };
}


#endif //__ContainerIterator_H_
