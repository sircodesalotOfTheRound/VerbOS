//
// Created by Reuben Kuhnert on 14/9/30.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __MemoryLabel_H_
#define __MemoryLabel_H_

#include <string>
#include <functional>
#include "Event.h"

namespace op {
  class MemoryLabel {
    void* memory_location_;
    std::string name_;

    helpers::Event<void(void*)> callbacks_;

  public:
    MemoryLabel(std::string name);
    MemoryLabel(std::string name, void* memory_location);

    std::string name() const;
    bool is_location_fixed() const;

    void set_location(void* memory_location);
    void add_callback(std::function<void(void*)> callback);
    void* memory_location() const { return memory_location_; }

  };
}


#endif //__MemoryLabel_H_
