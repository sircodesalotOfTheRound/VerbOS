//
// Created by Reuben Kuhnert on 14/9/29.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#ifndef __Variable_H_
#define __Variable_H_

#include "SystemType.h"

namespace jit {
  class Variable {
    const static int none = -1;

    int priority_;
    int variable_number_;
    const types::SystemType& type_;

    // Is this variable a member of some object?
    // (In particular does it require dereferencing to access?)
    bool is_member_;

    // Is this variable a class pointer?
    // That is does it point to the metadata of some class
    // that we can use either for reflection or dynamic programming?
    bool is_object_reference_;


  public:
    Variable(int variable_number, const types::SystemType& type, int priority, bool is_member, bool is_object_reference);

    int priority() const;
    int variable_number() const;
    const types::SystemType& type() const;
    bool is_member() const;
    bool is_object_reference() const;

  private:
    Variable(const Variable&) = delete;
    Variable(Variable&&) = delete;
    Variable& operator=(const Variable&) = delete;
    Variable& operator=(Variable&&) = delete;
  };
}



#endif //__Variable_H_
