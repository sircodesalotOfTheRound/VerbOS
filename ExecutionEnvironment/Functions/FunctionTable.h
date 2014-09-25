//
// Created by Reuben Kuhnert on 14/9/24.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __FunctionTable_H_
#define __FunctionTable_H_

#include <string>
#include <unordered_map>

namespace env {
  class FunctionTable {
    static std::unordered_map<std::string, void*> entries_;

  public:
    static void add(std::string name, void* location) {
      entries_.insert({ name, location });
    }

    static void* get(std::string name) {
      return entries_.at(name);
    }

    static bool contains(std::string name) {
      return entries_.find(name) != entries_.end();
    }
  };
}


#endif //__FunctionTable_H_
