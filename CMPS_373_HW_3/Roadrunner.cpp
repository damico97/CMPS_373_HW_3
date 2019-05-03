//
//  Roadrunner.cpp
//  CMPS_373_HW_3
//
//  Created by Joey Damico on 5/1/19.
//  Copyright © 2019 Joey Damico. All rights reserved.
//

#include "Agent.h"
#include "Roadrunner.h"

#include <iostream>

Roadrunner::Roadrunner(int nId) {
    this->agent_id = nId;
}

void Roadrunner::print_kind() {
    std::cout << "R";
}

std::string Roadrunner::get_kind() {
    return "R";
}
