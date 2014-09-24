//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __FileInt8_H_
#define __FileInt8_H_

#include <istream>

class FileInt8 {
  uint8_t value_;

public:
  FileInt8(std::istream& stream);

  uint8_t value() const;
  operator uint8_t() const;

  friend std::ostream& operator<<(std::ostream& stream, const FileInt8& file_int) {
    return stream << file_int.value_;
  }

};


#endif //__FileInt8_H_
