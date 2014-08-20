//
// Created by Reuben Kuhnert on 14/8/20.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <_types/_uint64_t.h>
#include "CpuRegister.h"

#ifndef __Operand_H_
#define __Operand_H_


enum class OperandType {

};

union ProcessorOpCodeOperand {
    uint64_t value;
    processor::CpuRegister* reg;
    processor::DereferencedCpuRegister *deref_reg;
};



#endif //__Operand_H_
