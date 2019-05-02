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
    Agent();
    Agent(int nId);
    void set_coords(int x, int y);
    int get_x_coord();
    int get_y_coord();
    int get_agent_id();
    void print_agent();
    virtual void print_kind() = 0;
    
protected:
    int agent_id;
    int counter_breed;
    int counter_die;
    int x_coord;
    int y_coord;
private:
};

#endif /* Agent_h */
