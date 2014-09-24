//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __FileInt32_H_
#define __FileInt32_H_

#include <istream>

class FileInt32 {
  uint32_t value_;

public:
  FileInt32(std::istream& stream);

  uint32_t value() const;
  operator uint32_t() const;

  friend std::ostream& operator<<(std::ostream& stream, const FileInt32& file_int) {
    return stream << file_int.value_;
  }

};


#endif //__FileInt32_H_
