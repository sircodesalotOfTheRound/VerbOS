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
    hla::Variable var1 { new_local("var1", vmint32) };
    hla::Variable var2 { new_local("var2", vmint32) };
    hla::Variable var3 { new_local("var3", vmint32) };
    hla::Variable var4 { new_local("var4", vmint32) };
    hla::Variable var5 { new_local("var5", vmint32) };
    hla::Variable var6 { new_local("var6", vmint32) };
    hla::Variable var7 { new_local("var7", vmint32) };
    hla::Variable var8 { new_local("var8", vmint32) };
    hla::Variable var9 { new_local("var9", vmint32) };
    hla::Variable var10 { new_local("var10", vmint32) };


public:
    MyFunction(void* memory) : HighLevelAssembler((byte*)memory, {2}) { }

    void on_build() override {

        var1 = 10;
        var2 = 20;

        ret(var2);

        var1 = 10;
        ret(var1);
    }
};


int main() {
    void* memory = mmap(nullptr, (size_t)getpagesize(), PROT_EXEC | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    MyFunction func(memory);
    func.build();


    int(*pfunc)() = (int(*)())memory;
    cout << pfunc() << endl;
}
