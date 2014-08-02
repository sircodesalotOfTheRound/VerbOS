
#ifndef RETOPCODE_H
#define RETOPCODE_H

#include "OpCode.h"

namespace opcodes {
    class ReturnOpCode : public OpCode {
    public:
        void render(jit::JitEmitter & writer);
        size_t size();
    };
}

#endif