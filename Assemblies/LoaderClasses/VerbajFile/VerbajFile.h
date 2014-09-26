//
// Created by Reuben Kuhnert on 14/9/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VerbajFile_H_
#define __VerbajFile_H_

#include <istream>
#include <memory>
#include <vector>
#include "ObjectImage.h"

namespace images {
  class VerbajFile {
    std::vector<std::unique_ptr<ObjectImage>> images_;

    using iterator = typename std::vector<std::unique_ptr<ObjectImage>>::iterator;

  public:
    void build_images(std::istream& stream);

    VerbajFile(std::istream& stream) {
      build_images(stream);
    }

    ObjectImage* add_image(std::istream& stream);

    iterator begin() { return images_.begin(); }
    iterator end() { return images_.end(); }
  };
}


#endif //__VerbajFile_H_
