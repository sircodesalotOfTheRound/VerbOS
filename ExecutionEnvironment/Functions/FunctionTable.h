//
// Created by Reuben Kuhnert on 14/9/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __FunctionTable_H_
#define __FunctionTable_H_

#include <string>
#include <unordered_map>
#include "FunctionImageLoader.h"

namespace env {
  class FunctionTable {
    static std::unordered_map<std::string, void*> entries_;
    static std::unordered_map<uintptr_t, std::string> call_stubs_;
    static std::unordered_map<std::string, images::FunctionImageLoader*> functions_;

  public:
    static void add(std::string name, void* location) {
      entries_.insert({ name, location });
    }

    static void* get(std::string name) {
      if (functions_.find(name) != functions_.end()){
        void *function_entry_point = functions_.at(name)->compile();
        functions_.erase(name);

        add(name, function_entry_point);
      }

      return entries_.at(name);
    }

    static bool contains(std::string name) {
      return entries_.find(name) != entries_.end();
    }

    static void add_stub(uintptr_t callfrom_location, std::string name) {
      call_stubs_.insert({ callfrom_location, name });
    }

    static std::string get_stub_from_location(uintptr_t location) {
      return call_stubs_.at(location);
    }

    static void add_unbuilt_function(images::FunctionImageLoader* function) {
      functions_.insert({ function->image_name(), function });
    }
  };
}


#endif //__FunctionTable_H_
