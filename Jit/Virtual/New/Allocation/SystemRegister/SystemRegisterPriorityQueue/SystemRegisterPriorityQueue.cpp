//
// Created by Reuben Kuhnert on 14/8/27.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "SystemRegisterPriorityQueue.h"

void jit::SystemRegisterPriorityQueue::prioritize() {
    // Rebuild the priority queue
    queue_ = std::priority_queue<SystemRegisterPriority>();

    for (auto& binding : bindings_) {
        // If the binding is locked (because a variable needs to sit on
        // a particular register, usually before a method call) then
        // we don't want to add that to the priority queue.
        if (!binding.is_locked()) {
            SystemRegisterPriority priority(binding.sys_register(), binding.priority(), binding.binding_number());
            queue_.push(priority);
        }
    }
}

jit::VirtualVariableSystemRegisterBinding& jit::SystemRegisterPriorityQueue::dequeue(const arch::CpuRegister& sys_register) {
    int sys_register_index = register_index_from_cpu_register(sys_register);

    // Circumventing the priority queue invalidates it.
    queue_invalidated_ = true;
    return bindings_[sys_register_index];
}

jit::VirtualVariableSystemRegisterBinding&& jit::SystemRegisterPriorityQueue::dequeue() {
    if (queue_invalidated_) {
        prioritize();
    }

    // Pop item from queue
    const SystemRegisterPriority& priority = queue_.top();
    queue_.pop();

    return std::move(bindings_[priority.register_index()]);
}

jit::VirtualVariableSystemRegisterBinding &jit::SystemRegisterPriorityQueue::get_binding(int virtual_register_number) {
    auto binding_number_iter = bound_variable_map_.find(virtual_register_number);

    if (binding_number_iter == bound_variable_map_.end()) {
        throw std::logic_error("variable is not bound");
    }

    return bindings_[binding_number_iter->second];
}

int jit::SystemRegisterPriorityQueue::register_index_from_cpu_register(const arch::CpuRegister &sys_register) {
    return register_map_.at(sys_register);
}

jit::VirtualVariable&& jit::SystemRegisterPriorityQueue::release(int virtual_register_index) {
    VirtualVariableSystemRegisterBinding& binding = get_binding(virtual_register_index);

    remove_metadata(binding);

    // return the variable.
    return std::move(binding.release_variable());
}

void jit::SystemRegisterPriorityQueue::bind_metadata(VirtualVariableSystemRegisterBinding& binding) {
    if (binding.contains_variable()) {
        // Erase from register lookup.
        register_map_.insert({binding.sys_register(), binding.variable_number()});

        // Erase from bound variable map.
        bound_variable_map_.insert({binding.variable_number(), binding.binding_number()});
    }
}
