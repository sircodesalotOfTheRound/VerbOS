//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VMString_H_
#define __VMString_H_

#include <cstddef>
#include <iostream>

namespace vm {
    class VMFieldNameString {
        uint16_t size_;
        char* text_;

    public:
        VMFieldNameString(size_t size, const char* text) : size_(size) {
            text_ = new char[size];
            strncpy(text_, text, size_);
        }

        ~VMFieldNameString() { delete [] text_; }

        VMFieldNameString(const VMFieldNameString & rhs) : size_(rhs.size_) {
            text_ = new char[size_];
            strncpy(text_, rhs.text_, size_);
        }

        VMFieldNameString(VMFieldNameString && rhs) : size_(rhs.size_), text_(rhs.text_) {
            rhs.size_ = 0;
            rhs.text_ = nullptr;
        }

        VMFieldNameString & operator=(const VMFieldNameString & rhs) {
            if (this == &rhs) return *this;

            if (size_ > 0) {
                delete [] text_;
            }

            size_ = rhs.size_;
            text_ = new char[size_];

            return *this;
        }

        VMFieldNameString & operator=(VMFieldNameString && rhs) {
            if (this == &rhs) return *this;

            if (size_ > 0) {
                delete[] rhs.text_;
            }

            size_ = rhs.size_;
            text_ = rhs.text_;

            rhs.size_ = 0;
            rhs.text_ = nullptr;

            return *this;
        }

        friend std::ostream& operator<<(std::ostream& stream, const VMFieldNameString & str) {
            for (int index = 0; index != str.size_; ++index)  {
                stream << str.text_[index];
            }

            return stream;
        }
    };
}


#endif //__VMString_H_
