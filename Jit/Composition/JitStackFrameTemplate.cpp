//
// Created by Reuben Kuhnert on 14-6-20.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "JitStackFrameTemplate.h"

void *jit::JitStackFrameTemplate::emit_to(JitEmitter &emitter) {
    // First take the address
    void *function_address = (void *) emitter.current_address();

    JitCodeSegment segment;
    segment.begin_frame();
    this->operations(segment);
    segment.end_frame();

    segment.emit_to(emitter);

    return function_address;
}