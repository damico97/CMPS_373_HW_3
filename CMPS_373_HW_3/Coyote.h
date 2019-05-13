/**
 * @file Coyote.h
 * @author Joey Damico
 * @date May 6, 2019
 * @brief Header file for the Coyote Class, this class inheirts from the Agent class
 *
 * CMPS 373 - Object Oriented Programming
 * Homework #3 - Roadrunners & Coyotes Simulator
 */

#include <vector>

#include "Agent.h"
#include "Coordinate.h"

#ifndef Coyote_h
#define Coyote_h

class Coyote: public Agent {
public:
    
    Coyote(int nId);
    void print_kind();
    std::string get_kind();
    void move(std::vector<std::vector<Agent*> > &board, int coyote_current_pop, int coyote_init_pop, int roadrunner_current_pop, int roadrunner_init_pop);
    
    Coordinate find_roadrunner(std::vector<std::vector<Agent*> > board);
    Coordinate find_new_coordinate(std::vector<std::vector<Agent*> > board, Coordinate current_location, bool look_for_roadrunner);
    
    void inc_die_counter();
    void reset_die_counter();
    int get_die_counter();
    bool check_if_dead();
    
    void inc_breed_counter();
    void reset_breed_counter();
    int get_breed_counter();
    bool check_can_breed(std::vector<std::vector<Agent*> > board);
    
protected:
    //int agent_id;
    //int counter_breed;
    //int counter_die;
    //Coordinate agent_location;
    
private:
    const int BREED = 8;
    const int STARVE = 4;
};

#endif /* Coyote_h */
