//
// Created by Reuben Kuhnert on 14/9/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __FileObjectTypeReader_H_
#define __FileObjectTypeReader_H_

#include <istream>
#include "TypeDef.h"

namespace images {
  class FileObjectTypeReader {
    uint16_t codes_;

  public:
    FileObjectTypeReader(std::istream& stream) {
      // TODO: Account for endianess!
      stream.read((char*)&codes_, sizeof(uint16_t));
    }

  public:
    const short image_type() const { return codes_; }
  };
}


#endif //__FileObjectTypeReader_H_
