//
//  Agent.cpp
//  CMPS_373_HW_3
//
//  Created by Joey Damico on 5/1/19.
//  Copyright © 2019 Joey Damico. All rights reserved.
//

#include "Agent.h"

#include <iostream>

Agent::Agent() {
    this->agent_id = NULL;
    this->counter_breed = 0;
    this->counter_die = 0;
}

Agent::Agent(int nId) {
    this->agent_id = nId;
    this->counter_breed = 0;
    this->counter_die = 0;
}

void Agent::set_coords(int x, int y) {
    this->x_coord = x;
    this->y_coord = y;
}

int Agent::get_x_coord() {
    return this->x_coord;
}

int Agent::get_y_coord() {
    return this->y_coord;
}

int Agent::get_agent_id() {
    return this->agent_id;
}

void Agent::print_agent() {
    std::cout << this->agent_id;
}
