//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __ClassBand_H_
#define __ClassBand_H_

#include "TypeDef.h"
#include "InstanceClassPointer.h"

namespace types {
  class SystemType;
  class Instance;
  struct Trait {
    Instance* instance_pointer_;

  public:
    // Should be initialized on 'new'. Empty constructor.
    Trait() { }

    Trait(Instance* instance) : instance_pointer_(instance) { }

    Instance& get_instance() const;
    const SystemType& def() const;

    template<class T>
    T* data() {
      return (T*) &(((byte*) this)[8]);
    }

    template<class T>
    T* data(off_t byte_offset) {
      return (T*) &((byte*) this)[byte_offset + 8];
    }

    // TODO: Access memory by named offset rather than by magic number.
  };
}

#endif //__ClassBand_H_
