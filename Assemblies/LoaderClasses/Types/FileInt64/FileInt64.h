//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __FileInt64_H_
#define __FileInt64_H_

#include <istream>

class FileInt64 {
  uint64_t value_;

public:
  FileInt64(std::istream& stream);

  uint64_t value() const;
  operator uint64_t() const;

  friend std::ostream& operator<<(std::ostream& stream, const FileInt64& file_int) {
    return stream << file_int.value_;
  }

};


#endif //__FileInt64_H_
