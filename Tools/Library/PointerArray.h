//
// Created by Reuben Kuhnert on 14/7/26.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#ifndef __PointerArray_H_
#define __PointerArray_H_

#include "Types.h"
#include <array>

namespace lib {
    template<class T, size_t T_size>
    class PointerArray {
        std::array<T *, T_size> array_;

        using iterator = typename std::array<T*, T_size>::iterator;

    public:
        PointerArray() {
            clear();
        }

        ~PointerArray() {
            release();
        }

        void clear() {
            for (T *pointer : array_) {
                pointer = nullptr;
            }
        }

        void release() {
            for (T *pointer : array_) {
                delete pointer;
            }
        }

        size_t size() {
            return T_size;
        }

        T *&operator[](int index) {
            return array_[index];
        }

        iterator begin() { return array_.begin(); }
        iterator end() { return array_.end(); }

    private:
        PointerArray(const PointerArray &) = delete;

        PointerArray(const PointerArray &&) = delete;

        PointerArray &operator=(const PointerArray &) = delete;

        PointerArray &operator=(const PointerArray &&) = delete;
    };
}


#endif //__PointerArray_H_
