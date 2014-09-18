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
      SystemRegisterPriority priority(binding);
      queue_.push(priority);
    }
  }
}

jit::VirtualVariableSystemRegisterBinding&& jit::SystemRegisterPriorityQueue::dequeue(const arch::CpuRegister& sys_register) {
  int sys_register_index = register_index_from_cpu_register(sys_register);

  VirtualVariableSystemRegisterBinding&& binding = std::move(bindings_[sys_register_index]);

  remove_metadata(binding);

  // Circumventing the priority queue invalidates it.
  queue_invalidated_ = true;

  return std::move(binding);
}

jit::VirtualVariableSystemRegisterBinding&& jit::SystemRegisterPriorityQueue::dequeue(int virtual_variable) {
  int register_binding_index = bound_variable_map_.at(virtual_variable);

  VirtualVariableSystemRegisterBinding&& binding = std::move(bindings_[register_binding_index]);
  remove_metadata(binding);

  // Circumventing the priority queue like this invalidates it.
  queue_invalidated_ = true;

  return std::move(binding);
}


jit::VirtualVariableSystemRegisterBinding&& jit::SystemRegisterPriorityQueue::dequeue() {
  if (queue_invalidated_) {
    prioritize();
  }

  // Pop item from queue
  const SystemRegisterPriority& priority = queue_.top();
  queue_.pop();

  VirtualVariableSystemRegisterBinding&& binding = std::move(bindings_[priority.binding_number()]);
  remove_metadata(binding);

  return std::move(binding);
}

int jit::SystemRegisterPriorityQueue::register_index_from_cpu_register(const arch::CpuRegister& sys_register) {
  return register_map_.at(sys_register);
}

void jit::SystemRegisterPriorityQueue::bind_metadata(VirtualVariableSystemRegisterBinding& binding) {
  // Map the system-register to the binding number.
  register_map_.insert({binding.sys_register(), binding.binding_number()});

  // If there is a variable, map the variable number to the binding number.
  if (binding.contains_variable()) {
    // Erase from bound variable map.
    bound_variable_map_.insert({binding.variable_number(), binding.binding_number()});
  }
}
