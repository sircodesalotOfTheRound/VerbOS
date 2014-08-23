//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __ProcessorOpCodeBase_H_
#define __ProcessorOpCodeBase_H_

#include <string>
#include <sstream>
#include <iostream>
#include "TypeDef.h"
#include "JitRenderer.h"
namespace op {
    struct ProcessorOpCodeBase {
        virtual ~ProcessorOpCodeBase() { }

        virtual std::string rep() const = 0;
        virtual size_t size() const = 0;
        virtual void render(jit::JitRenderer&) const = 0;

        friend std::ostream& operator<<(std::ostream& stream, const ProcessorOpCodeBase& op_code) {
            return stream << op_code.rep();
        }
    };
}


#endif //__ProcessorOpCodeBase_H_
