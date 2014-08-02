//
// Created by Reuben Kuhnert on 14/8/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//


#ifndef __VariableComparison_H_
#define __VariableComparison_H_

#include <iostream>

namespace hla {

    enum class VARIABLE_COMPARISON {
        EQUALS,
        NOT_EQUALS,
        GREATER_THAN_OR_EQUALS,
        GREATER_THAN,
        LESS_THAN,
        LESS_THAN_OR_EQUALS,

        NONE,
        SOME
    };

    class VariableComparison {
        VARIABLE_COMPARISON comparison_;
        std::string type_;

    public:
        VariableComparison(VARIABLE_COMPARISON comparison) : comparison_ (comparison) { }

        VARIABLE_COMPARISON comparison() { return comparison_; }

        friend std::ostream& operator<<(std::ostream& stream, const VariableComparison& comparison) {
            using namespace std;
            switch (comparison.comparison_) {
                case VARIABLE_COMPARISON::EQUALS: cout << "equals"; break;
                case VARIABLE_COMPARISON::NOT_EQUALS: cout << "not equals"; break;

                case VARIABLE_COMPARISON::LESS_THAN: cout << "less than"; break;
                case VARIABLE_COMPARISON::LESS_THAN_OR_EQUALS: cout << "less than or equals"; break;
                case VARIABLE_COMPARISON::GREATER_THAN: cout << "greater than"; break;
                case VARIABLE_COMPARISON::GREATER_THAN_OR_EQUALS: cout << "greater than or equals"; break;

                case VARIABLE_COMPARISON::SOME: cout << "some"; break;
                case VARIABLE_COMPARISON::NONE: cout << "none"; break;
            }

            return stream;
        }
    };

}


#endif //__VariableComparison_H_
