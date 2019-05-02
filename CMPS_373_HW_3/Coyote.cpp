//
//  Coyote.cpp
//  CMPS_373_HW_3
//
//  Created by Joey Damico on 5/2/19.
//  Copyright © 2019 Joey Damico. All rights reserved.
//

#include "Agent.h"
#include "Coyote.h"

#include <iostream>

Coyote::Coyote(int nId) {
    this->agent_id = nId;
}

void Coyote::print_kind() {
    std::cout << "C";
}
