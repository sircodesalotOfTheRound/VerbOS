//
// Created by Reuben Kuhnert on 14/8/2.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __SystemArchitecture_H_
#define __SystemArchitecture_H_

template<class RegisterSet>
class SystemArchitecture {
    RegisterSet registers_;

public:
    RegisterSet registers() { return registers_; }
};


#endif //__SystemArchitecture_H_
