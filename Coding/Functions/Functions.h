//
// Created by Reuben Kuhnert on 14/8/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __Functions_H_
#define __Functions_H_

#include <functional>

namespace helpers {
    void stack_aligned_call(std::function<void()> callback);
}


#endif //__Functions_H_
