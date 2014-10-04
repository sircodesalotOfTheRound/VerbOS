//
// Created by Reuben Kuhnert on 14/10/4.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <vector>
#include <unordered_map>
#include <sys/mman.h>
#include <unistd.h>
#include "TypeDef.h"

#ifndef __MemoryAllocator_H_
#define __MemoryAllocator_H_

namespace gc {
  class MemoryAllocator {
    size_t used_space_;
    size_t remaining_space_;
    void* page_;

  public:
    MemoryAllocator() :
      used_space_(0),
      remaining_space_((size_t)getpagesize()),
      page_(create_page())
    {

    }

    void* allocate(size_t size) {
      void* address = (void*)(((byte*)page_) + used_space_ + size);
      used_space_ += size;
      remaining_space_ -= size;

      if (remaining_space_ < size) {
        throw std::logic_error("out of memory exception");
      }

      return address;
    }

    size_t used_space() const { return used_space_; }
    size_t remaining_space() const { return remaining_space_; }

  private:
    void* create_page() {
      return mmap(nullptr, (size_t) getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    }

    MemoryAllocator(const MemoryAllocator&) = delete;
    MemoryAllocator(MemoryAllocator&&) = delete;
    MemoryAllocator& operator=(const MemoryAllocator&) = delete;
    MemoryAllocator& operator=(MemoryAllocator&&) = delete;
  };
}


#endif //__MemoryAllocator_H_
