//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef SYSTEM_STRING
#define SYSTEM_STRING

#include <string>
#include <iostream>
#include "TypeDef.h"

class SystemString {
    // TODO: Align the memory to ensure no gaps.
    uint32_t length_;
    char* text_;

public:
    SystemString(const char* text, size_t length) : length_((uint32_t)length), text_(new char[length_])  {
        strncpy(text_, text, length);
    }

    SystemString(std::string source) : SystemString(source.c_str(), source.size()) {

    }

    SystemString(const SystemString& rhs) {
        length_ = rhs.length_;
        text_ = new char[length_];

        strncpy(text_, rhs.text_, length_);
    }

    SystemString(SystemString&& rhs) : length_(rhs.length_), text_(rhs.text_) {
        rhs.length_ = 0;
        rhs.text_ = nullptr;
    }

    SystemString& operator=(const SystemString& rhs) {
        if (this == &rhs) return *this;

        delete[] text_;
        length_ = rhs.length_;
        text_ = new char[length_];

        strncpy(text_, rhs.text_, length_);

        return *this;
    }


    ~SystemString() {
        length_ = 0;
        delete[] text_;
    }


    friend std::ostream& operator<<(std::ostream& stream, const SystemString& str) {
        for (int index = 0; index != str.length_; index++) {
            stream << str.text_[index];
        }

        return stream;
    }

    const char* c_str() const { return text_; }
    uint32_t length() const { return length_; }
    std::string str() const { return { text_, length_ }; }
};


#endif //SYSTEM_STRING
