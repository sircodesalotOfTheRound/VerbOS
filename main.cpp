//
//  main.cpp
//  VerbOS
//
//  Created by Reuben Kuhnert on 14/7/31.
//  Copyright (c) 2014年 Reuben Kuhnert. All rights reserved.
//

#include <iostream>
#include "HighLevelAssembler.h"
#include "VMFieldNameString.h"
#include "ForwardAllocator.h"
#include "Types.h"
#include "sys/mman.h"
#include "unistd.h"
#include "JitEmitter.h"
#include "JitCodeSegment.h"
#include "LowLevelAssembler.h"
#include "RegisterAllocator.h"

using namespace std;
using namespace jit;

const typesys::VerbosType vmint32 { "::vmint32" };

class MyFunction : public hla::HighLevelAssembler {
    hla::Variable var {new_local("var", vmint32) };


public:
    MyFunction(void* memory) : HighLevelAssembler((byte*)memory, {2}) { }

    void on_build() override {
        var = 10;
        var += 30;
        ret();
    }
};


int main() {
    void* memory = mmap(nullptr, (size_t)getpagesize(), PROT_EXEC | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    MyFunction func(memory);
    func.build();


    int(*pfunc)() = (int(*)())memory;
    cout << pfunc() << endl;
}
