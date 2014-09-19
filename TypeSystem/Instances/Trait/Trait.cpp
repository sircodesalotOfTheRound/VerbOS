//
// Created by Reuben Kuhnert on 14/9/1.
// Copyright (c) 2014 Reuben Kuhnert. All rights reserved.
//

#include "Trait.h"
#include "Instance.h"

const types::SystemType& types::Trait::def() const { return get_instance().type(); }