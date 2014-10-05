//
// NOTE: The layout of an instance is directly tied to system architecture!
// This is done to simplify accessing the instance content from assembly.
//


#ifndef __SystemTypeInstance_H_
#define __SystemTypeInstance_H_

#include "TypeDef.h"
#include "SystemType.h"
#include "Trait.h"

namespace types {
  class Trait;
  class SystemType;
  class Instance {
    // 16 byte header. (System type, and GC meta info).
    const SystemType* type_;
    Trait head_trait_;

  public:
    Instance() { }

    // For constructing normal objects:
    void* operator new(size_t size, const SystemType& type);

    // For constructing arrays:
    void* operator new(size_t size, const SystemType& type, size_t additional_size);

    Trait* head();
    const SystemType& type() const;
    size_t member_offset(std::string name) const;

  private:
    Instance(const SystemType& type)
      : type_(&type),
        head_trait_(this)
    {

    }

    void* operator new(size_t size, size_t required_size);

    // Dissallow movement for now
    Instance(const Instance&) = delete;
    Instance(Instance&&) = delete;
    Instance operator=(const Instance&) = delete;
    Instance operator=(Instance&&) = delete;

  };
}


#endif //__SystemTypeInstance_H_
