//
// Created by Reuben Kuhnert on 14-6-23.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "CallStub.h"
/*
std::unordered_map<uintptr_t, std::pair<vm::ExecutionEnvironment, std::string>> CallStub::items_;

void CallStub::patch_call() {
    using namespace std;
    using namespace opcodes;
    using namespace jit;

    // The address that called this function.
    uintptr_t callfrom_location = 0;

    // Read the address that called this function
    // from the call stack.
    __asm {
        mov rax, [rbp + 8]              ; [RBP + 8]: Return address just above RBP.
        sub rax, 5                      ; Subtract 5 from the call address.
        mov [callfrom_location], rax    ; Save the callfrom_location
    }

    byte* memory = (byte*)callfrom_location;

    jit::JitEmitter emitter { memory };

    // The function to emit.
    // emitter.emit(CallOpCode((void*)a_function));

    // Clear the stack and force a return to the newly patched address.
    // This will recall the function with the correctly patched address.
    __asm {
        mov rsp, rbp                    ; Force reset the stack pointer
        pop rbp                         ; Reset the base pointer
        add rsp, 8                      ; Erase the ret address

        mov rax, 0                      ; Zeroize ret value.

        jmp [callfrom_location]         ; Jump to the patched function
    }
}


void CallStub::render(jit::JitEmitter &emitter) {
    using namespace std;
    using namespace opcodes;
    using namespace reg;

    uintptr_t call_location = emitter.current_address();
    items_.insert(make_pair(call_location, function_call_));

    emitter.emit(CallOpCode((void *) patch_call));
}
*/