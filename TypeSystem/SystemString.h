//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef SYSTEM_STRING
#define SYSTEM_STRING

#include <string>
#include <iostream>
#include "TypeDef.h"

class SystemString {
  byte* data_;

public:
  SystemString(const char* text, size_t length) : data_(allocate_memory(length)) {
    set_length(length);
    memcpy(&data_[4], text, length);
  }

  SystemString(std::string source) : SystemString(source.c_str(), source.size()) {

  }

  SystemString(const SystemString& rhs) {
    data_ = allocate_memory(rhs.length());
    memcpy(data_, rhs.data_, length());
  }

  SystemString(SystemString&& rhs) : data_(rhs.data_) {
    rhs.data_ = nullptr;
  }

  SystemString& operator=(const SystemString& rhs) {
    if (this == &rhs) return *this;

    delete[] data_;
    memcpy(data_, rhs.data_, rhs.length());

    return *this;
  }

  ~SystemString() {
    delete[] data_;
  }


  friend std::ostream& operator<<(std::ostream& stream, const SystemString& str) {
    uint32_t length = str.length();

    for (int index = 0; index != length; index++) {
      stream << ((char*) str.data_)[index + 4];
    }

    return stream;
  }

  const byte* address() const {
    return data_;
  };

  uint32_t length() const {
    return *(uint32_t*) data_;
  }

  std::string str() const {
    return {&((const char*) data_)[4], length()};
  }

private:
  byte* allocate_memory(size_t size) {
    return new byte[size + sizeof(uint32_t)];
  }

  void set_length(size_t size) {
    ((uint32_t*) data_)[0] = (uint32_t) size;
  }
};


#endif //SYSTEM_STRING
