//
// Created by Reuben Kuhnert on 14-6-12.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <vector>
#include "Types.h"
#include <sstream>

#ifndef VLIT_TYPES_H
#define VLIT_TYPES_H

template<class T>
class vlit {
    T _value;

public:
    vlit(std::istream& stream) {
        stream.read((char*)&_value, sizeof(T));
    }

    vlit<T>& operator=(int rhs) {
        _value = rhs;
        return *this;
    }

    operator T() const { return _value; }

    friend std::ostream& operator<<(std::ostream& stream, const vlit<T>& value) {
        return stream << (int)value;
    }
};


class vlit_string {
    std::string text_;

public:
    vlit_string(std::istream& stream) : text_(consume_text(stream))
    {

    }


    std::string str() { return text_; }
    const char& operator[](int index) const { return text_[index]; }
    friend std::ostream& operator<<(std::ostream& stream, const vlit_string& text) {
        return stream << text.text_;
    }

private:
    std::string consume_text(std::istream& stream) {
        vlit<int16> size { stream };

        char buffer[(int)size + 1];
        buffer[int(size)] = 0;

        stream.read(buffer, size);

        return std::string { buffer };
    }
};

template<class T_size, class T>
class vlit_array {
    T_size _size;
    std::vector<T*> _items;

public:

    vlit_array(std::istream& stream) : _size(stream) {
        for (int index = 0; index != _size; ++index) {
            _items.push_back(new T(stream));
        }

        using namespace std;
    }

    T_size size() { return _size; };

    T& operator[](int index) { return *_items[index]; }

    std::vector<T*> vector() { return _items; }

    T* begin() { return _items[0]; }
    T* end() { return _items[(int)_size]; }
};

class vlit_parameter {
    vlit_string _name;
    vlit_string _type;

public:
    vlit_parameter(std::istream& stream)
        : _name(stream),
        _type(stream)
    {

    }

    vlit_string& name() { return _name; }
    vlit_string& type() { return _type; }

    friend std::ostream& operator<<(std::ostream& stream, const vlit_parameter& parameter) {
        return stream << parameter._name << " : " << parameter._type;
    }
};

#endif //__VlitTypes_H_
