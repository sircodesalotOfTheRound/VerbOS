//
// Created by Reuben Kuhnert on 14/8/19.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef SYSTEM_TYPE
#define SYSTEM_TYPE

#include <string>
#include "TypeDef.h"
#import "SystemString.h"

class SystemType {
    byte* data_;

public:
    SystemType(std::string name) : data_(allocate_memory()) {
        write_name(name);
    }

    SystemType(const SystemType&) = delete;
    SystemType(SystemType&&) = delete;
    SystemType& operator=(const SystemType&) = delete;
    SystemType& operator=(SystemType&&) = delete;

    ~SystemType() { delete[] data_; }

private:
    byte* allocate_memory() {
        static int SIZEOF_NAME = sizeof(SystemString);

        return new byte[SIZEOF_NAME];
    }

    void write_name(std::string name) {
        data_ = (byte*)new SystemString(name);
    }

    friend std::ostream& operator<<(std::ostream& stream, const SystemType& type) {
        return stream << *(SystemString*)type.data_;
    }
};


#endif //SYSTEM_TYPE
