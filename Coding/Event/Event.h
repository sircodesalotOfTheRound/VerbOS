//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//



#ifndef __Event_H_
#define __Event_H_

#include <functional>
#include <vector>

namespace helpers {
  template<class T>
  class Event {
    std::vector<std::function<T>> callbacks_;
    using iterator = typename std::vector<std::function<T>>::iterator;

  public:
    void add(std::function<T> callback) {
      callbacks_.push_back(callback);
    }

    template<typename ... Args>
    void update(Args... value) {
      for (auto& callback : callbacks_) {
        callback(value ...);
      }
    }
  };
}


#endif //__Event_H_
