/**
 * @file Agent.h
 * @author Joey Damico
 * @date May 6, 2019
 * @brief Header for the Agent Class
 *
 * CMPS 373 - Object Oriented Programming
 * Homework #3 - Roadrunners & Coyotes Simulator
 */

#include <vector>

#include "Coordinate.h"


#ifndef Agent_h
#define Agent_h

class Agent {
public:
    Agent();
    Agent(int nId);
    void set_moved();
    void reset_moved();
    bool checked_moved();
    void set_coords(int x, int y);
    Coordinate get_location();
    int get_agent_id();
    void print_agent();
    
    // Virtual functions that are defined in the Coyote & Roadrunner Classes 
    virtual void print_kind() = 0;
    virtual std::string get_kind() = 0;
    virtual void move(std::vector<std::vector<Agent*> > &board, int coyote_current_pop, int coyote_init_pop, int roadrunner_current_pop, int roadrunner_init_pop) = 0;
    virtual Coordinate find_roadrunner(std::vector<std::vector<Agent*> > board) = 0;
    virtual Coordinate find_new_coordinate(std::vector<std::vector<Agent*> > board, Coordinate current_location, bool look_for_roadrunner) = 0;
    
protected:
    int agent_id;
    int counter_breed;
    int counter_die;
    Coordinate agent_location;
    
private:
    bool moved;
};

#endif
/* Agent_h */
