//
// Created by Reuben Kuhnert on 14/9/26.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "VerbajFile.h"
#import "FileObjectTypeReader.h"
#include "FunctionImageLoader.h"

void images::VerbajFile::build_images(std::istream& stream) {
  while (!stream.eof()) {
    images_.push_back(std::unique_ptr<ObjectImage>(add_image(stream)));
    stream.peek();
  }
}

images::ObjectImage* images::VerbajFile::add_image(std::istream& stream) {
  using namespace images;
  FileObjectTypeReader type (stream);


  if (type.image_type() == 0x1111) {
    return new FunctionImageLoader(stream);
  }

  throw std::logic_error("not yet implemented");
}
