//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __Collector_H_
#define __Collector_H_

#include <memory>
#include <vector>

namespace helpers {
  template<class T>
  class AutoCollector {
    std::vector <std::unique_ptr<T>> items_;

  public:
    T* add(T* item) {
      items_.push_back(std::unique_ptr<T>(item));
      return item;
    }
  };
}


#endif //__Collector_H_
