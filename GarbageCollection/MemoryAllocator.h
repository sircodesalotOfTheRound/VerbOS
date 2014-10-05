//
// Created by Reuben Kuhnert on 14/10/4.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#include <vector>
#include <unordered_map>
#include <sys/mman.h>
#include <unistd.h>
#include "TypeDef.h"
#include "Instance.h"
#include "GarbageCollectionHeader.h"

#ifndef __MemoryAllocator_H_
#define __MemoryAllocator_H_

namespace gc {
  class MemoryAllocator {
    size_t used_space_;
    size_t remaining_space_;
    void* page_;
    void* next_address_;

  public:
    MemoryAllocator() :
      used_space_(0),
      remaining_space_((size_t)getpagesize()),
      page_(create_page()),
      next_address_(page_)
    {

    }

    void* allocate(size_t size) {
      using namespace types;

      size_t consumed_space = size + sizeof(GarbageCollectionHeader*);

      // Make sure we have enough space for this.
      if (remaining_space_ < size) {
        throw std::logic_error("out of memory exception");
      }

      // First get the next free address.
      byte* free_address = (byte*)next_address_;

      // Initialize the garbage collection header.
      types::GarbageCollectionHeader* gc_header = (GarbageCollectionHeader*)free_address;
      gc_header->set_visited(false);

      // Next free address is passed the garbage collection header..
      free_address += sizeof(GarbageCollectionHeader*);

      next_address_ = ((byte*)next_address_) + size;

      used_space_ += consumed_space;
      remaining_space_ -= consumed_space;

      return free_address;
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
