//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VMString_H_
#define __VMString_H_

#include <cstddef>
#include <iostream>

namespace vm {
    class VMString {
        uint16_t size_;
        char* text_;

    public:
        VMString(std::string str) : VMString(str.size(), str.c_str()) {

        }

        VMString(size_t size, const char* text) : size_(size) {
            text_ = new char[size];
            strncpy(text_, text, size_);
        }

        ~VMString() { delete [] text_; }

        VMString(const VMString & rhs) : size_(rhs.size_) {
            text_ = new char[size_];
            strncpy(text_, rhs.text_, size_);
        }

        VMString(VMString && rhs) : size_(rhs.size_), text_(rhs.text_) {
            rhs.size_ = 0;
            rhs.text_ = nullptr;
        }

        VMString & operator=(const VMString & rhs) {
            if (this == &rhs) return *this;

            if (size_ > 0) {
                delete [] text_;
            }

            size_ = rhs.size_;
            text_ = new char[size_];

            return *this;
        }

        VMString & operator=(VMString && rhs) {
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

        std::string str() const { return std::string(&text_[0], &text_[size_]); }

        friend std::ostream& operator<<(std::ostream& stream, const VMString & str) {
            for (int index = 0; index != str.size_; ++index)  {
                stream << str.text_[index];
            }

            return stream;
        }
    };
}


#endif //__VMString_H_
