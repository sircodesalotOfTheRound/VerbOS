//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __TypeComparison_H_
#define __TypeComparison_H_

#include <iostream>

namespace hla {
    enum class TYPE_COMPARISON {
        ISA,
        HASA,
        DOESA
    };

    class TypeComparison {
        TYPE_COMPARISON relation_;
        std::string type_;

    public:
        TypeComparison(TYPE_COMPARISON relation, std::string type) : relation_(relation), type_(type) { }

        TYPE_COMPARISON relation() { return relation_; }

        friend std::ostream& operator<<(std::ostream& stream, const TypeComparison& comparison) {
            using namespace std;
            switch (comparison.relation_) {
                case TYPE_COMPARISON ::ISA: cout << "is-a " << comparison.type_; break;
                case TYPE_COMPARISON ::HASA: cout << "has-a " << comparison.type_; break;
                case TYPE_COMPARISON ::DOESA: cout << "does-a " << comparison.type_; break;
            }

            return stream;
        }
    };
}


#endif //__TypeComparison_H_
