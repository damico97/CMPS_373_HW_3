//
//  Agent.h
//  CMPS_373_HW_3
//
//  Created by Joey Damico on 5/1/19.
//  Copyright © 2019 Joey Damico. All rights reserved.
//

#ifndef Agent_h
#define Agent_h

class Agent {
public:
    Agent(int nId);
    void print_agent();
    
protected:
    int agent_id;
    int counter_breed;
    int counter_die;
private:
};

#endif /* Agent_h */
