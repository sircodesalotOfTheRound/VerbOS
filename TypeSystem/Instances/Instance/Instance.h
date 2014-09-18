//
// NOTE: The layout of an instance is directly tied to system architecture!
// This is done to simplify accessing the instance content from assembly.
//


#ifndef __SystemTypeInstance_H_
#define __SystemTypeInstance_H_

#include <stdlib.h>
#include "TypeDef.h"
#import "SystemType.h"
#import "InstanceHeader.h"
#import "InstanceClassPointer.h"
#import "Trait.h"

namespace types {
  class Instance {
    // 16 byte header. (System type, and GC meta info).
    InstanceHeader header_;
    Trait head_trait_;

  public:
    Instance() {
    }

    void* operator new(size_t size, const SystemType& type) {
      // Initialize the memory after creating it.
      // Since we have everything we need to build the
      // type right here. Then return and allow default (empty)
      // constructor to run.
      size_t total_required_size = type.required_size() + sizeof(InstanceHeader);
      std::cout << "allocating:" << total_required_size << std::endl;
      return new(total_required_size) Instance(type);
    }

    Trait& head() {
      return head_trait_;
    }

    const SystemType& type() const {
      return header_.type();
    }

  private:
    Instance(const SystemType& type) : header_(type), head_trait_(this) {
    }

    void* operator new(size_t size, size_t required_size) {
      // Todo: Instances should use their own allocator, since they are only created (never destroyed)
      // except when all types in the environment are destroyed as well. Thus we can save memory
      // by creating a 'write once' allocator.
      return malloc(required_size);
    }

    // Dissallow movement for now.
    Instance(const Instance&) = delete;

    Instance(Instance&&) = delete;

    Instance operator=(const Instance&) = delete;

    Instance operator=(Instance&&) = delete;

  };
}


#endif //__SystemTypeInstance_H_
