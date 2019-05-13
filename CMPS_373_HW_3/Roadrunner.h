/**
 * @file Roadrunner.h
 * @author Joey Damico
 * @date May 6, 2019
 * @brief Main cpp file for the Roadrunner Class, this class inheirts from the Agent class
 *
 * CMPS 373 - Object Oriented Programming
 * Homework #3 - Roadrunners & Coyotes Simulator
 */

#include "Agent.h"

#ifndef Roadrunner_h
#define Roadrunner_h

class Roadrunner: public Agent {
public:
    Roadrunner(int nId);
    void print_kind();
    std::string get_kind();
    void move(std::vector<std::vector<Agent*> > &board, int coyote_current_pop, int coyote_init_pop, int roadrunner_current_pop, int roadrunner_init_pop);

    Coordinate find_roadrunner(std::vector<std::vector<Agent*> > board);
    Coordinate find_new_coordinate(std::vector<std::vector<Agent*> > board, Coordinate current_location, bool look_for_roadrunner);
    
    void inc_breed_counter();
    void reset_breed_counter();
    int get_breed_counter();
    bool check_can_breed(std::vector<std::vector<Agent*> > board);
    
private:
    const int BREED = 3;
};

#endif /* Roadrunner_h */
