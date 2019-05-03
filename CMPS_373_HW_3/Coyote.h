//
//  Coyote.h
//  CMPS_373_HW_3
//
//  Created by Joey Damico on 5/2/19.
//  Copyright © 2019 Joey Damico. All rights reserved.
//
#include <vector>

#include "Agent.h"

#ifndef Coyote_h
#define Coyote_h

class Coyote: public Agent {
public:
    Coyote(int nId);
    void print_kind();
    std::string get_kind();
    
protected:
    
private:
    const int BREED = 8;
    const int STARVE = 4;
};

#endif /* Coyote_h */
