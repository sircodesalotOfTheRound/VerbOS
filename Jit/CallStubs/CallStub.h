//
// Created by Reuben Kuhnert on 14-6-23.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//



#ifndef CALL_STUB_H
#define CALL_STUB_H

#include <string>
#include <iostream>
#include <unordered_map>

#include "OpCode.h"
#include "CallOpCode.h"
#include "MovOpCode.h"
#include "JitEmitter.h"

namespace vm {
    class ExecutionEnvironment;
}

class CallStub : public opcodes::OpCode {
/*
    struct FunctionCall {
        vm::ExecutionEnvironment& environment;
        std::string function_name;

        FunctionCall(vm::ExecutionEnvironment &environment, std::string function_name)
                : environment(environment),
                  function_name(function_name) {

        }
    };

public:
    CallStub(vm::ExecutionEnvironment &envrionment, std::string function_name)
            : function_call_(envrionment, function_name)
    {

    }

    size_t size() { return 5; };

    void render(jit::JitEmitter &emitter);

    static void patch_call();

private:
    static std::unordered_map<uintptr_t, std::pair<vm::ExecutionEnvironment, std::string>> items_;
    std::pair<vm::ExecutionEnvironment, std::string> function_call_;
    */
};

#endif
