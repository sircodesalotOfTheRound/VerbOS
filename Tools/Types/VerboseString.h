//
// Created by Reuben Kuhnert on 14-6-19.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#ifndef __VerboseString_H_
#define __VerboseString_H_

#include <string.h>
#include <iostream>
#include "Types.h"

class VerboseString {
    size_t _size;
    char *_string;
    int _hash;

    public:

    VerboseString(char* string)
        : _size(strlen(string)),
        _string(new char[_size])
    {
        _hash = copy_and_compute_hash(string);
    }

    VerboseString(const VerboseString& rhs) :
        _size(rhs._size),
        _string(new char[_size])
    {
        _hash = copy_and_compute_hash(rhs._string);
    }

    VerboseString(VerboseString&& rhs) :
        _size(rhs._size),
        _string(rhs._string),
        _hash(rhs._hash)
    {
        rhs._size = 0;
        rhs._hash = 0;
        rhs._string = nullptr;
    }

    VerboseString operator=(const VerboseString& rhs) {
        if (this == &rhs) return *this;

        // Delete existing string content.
        delete [] _string;

        _size = rhs._size;
        _string = new char[_size];
        _hash = copy_and_compute_hash(rhs._string);

        return *this;
    }

    VerboseString operator=(VerboseString&& rhs) {
        if (this == &rhs) return *this;

        // Delete existing string content.
        delete [] _string;

        _size = rhs._size;
        _hash = rhs._hash;
        _string = rhs._string;

        return *this;
    }

    ~VerboseString() { delete[] _string; }

    bool operator==(VerboseString& rhs) {
        if (this->_hash != rhs._hash) return false;
        if (this->_size != rhs._size) return false;

        return (strncmp(_string, rhs._string, _size) == 0);
    }

    int copy_and_compute_hash(const char *string) {
        int hash = 0;
        for (int index = 0; index != _size; ++index) {
            _string[index] = string[index];
            hash += ((_string[index] * 1051) + (hash * 1811));
        }

        return hash;
    }

    friend std::ostream& operator<<(std::ostream& stream, const VerboseString& string) {
        for (int index = 0; index != string._size; ++index) {
            stream << string._string[index];
        }

        return stream;
    }

    const char operator[](int index) { return _string[index]; }
    const char* c_str() { return _string; }
    size_t size() { return _size; }
    int hash() { return _hash; }

};


#endif //__VerboseString_H_
