#ifndef OPCODES_H
#define OPCODES_H

#include "Types.h"
#include "JitEmitter.h"

namespace jit {
    class JitEmitter;
}

namespace opcodes {
    class OpCode {

    protected:
        class Operand {
            union {
                uint64 _value;
                sysarch::p_sys_register _reg;
                void* _pointer;
            };

        public:
            enum optype {
                CONSTANT,
                REGISTER,
                POINTER
            } _type;

            Operand(sysarch::p_sys_register reg) : _reg(reg), _type(REGISTER) { }
            Operand(uint64 value) : _value(value), _type(CONSTANT) { }
            Operand(void* pointer) : _pointer(pointer), _type(POINTER) { }

            optype type() { return _type; }

            uint64 value() const { return _value; }
            sysarch::p_sys_register reg() const { return _reg; }
            void* pointer() { return _pointer; }
        };

    public:
        virtual ~OpCode() { }

        virtual size_t size() = 0;
        virtual void render(jit::JitEmitter& emitter) = 0;
    };
}

#endif