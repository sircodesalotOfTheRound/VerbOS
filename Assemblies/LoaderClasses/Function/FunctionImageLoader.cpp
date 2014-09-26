//
// Created by Reuben Kuhnert on 14/9/23.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "FunctionImageLoader.h"
#include "VerbajPrimitives.h"
#include <iostream>

using namespace types;
using namespace verbaj;
using namespace std;

void images::FunctionImageLoader::print(Trait* object) {
  auto& type = object->def();

  if (type.isa(VerbajPrimitives::vm_box_of_uint64)) {
    cout << "the boxed value: " << object->data<uint64_t>()[0] << endl;

  }
  else if (type.isa(VerbajPrimitives::vm_utf8)) {
    uint64_t length = object->data<uint64_t>()[0];

    for (int index = 0; index != length; ++index) {
      cout << object->data<char>(8)[index];
    }
  }

  cout << endl;
  //cout << endl << "this is a: " << type << endl;
}