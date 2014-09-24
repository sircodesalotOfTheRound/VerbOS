//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <iostream>
#include <istream>
#include "FileInt32.h"

#ifndef __FileString_H_
#define __FileString_H_


class FileString {
  std::string text_;

public:
  FileString(std::istream& stream) : text_(load_string(stream)) { }


  std::string text() const;
  operator std::string() const;

  friend std::ostream& operator<<(std::ostream& stream, const FileString& string) {
    return stream << string.text_;
  }

private:
  std::string load_string(std::istream& stream) {
    FileInt32 length(stream);

    char buffer[256];
    stream.read(buffer, length);

    buffer[length] = 0;
    return std::string(buffer);
  }
};


#endif //__FileString_H_
