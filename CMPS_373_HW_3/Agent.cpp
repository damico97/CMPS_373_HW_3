//
//  Agent.cpp
//  CMPS_373_HW_3
//
//  Created by Joey Damico on 5/1/19.
//  Copyright © 2019 Joey Damico. All rights reserved.
//

#include "Agent.h"

#include <iostream>


Agent::Agent(int nId) {
    this->agent_id = nId;
    this->counter_breed = 0;
    this->counter_die = 0;
}

void Agent::print_agent() {
    std::cout << this->agent_id;
}
