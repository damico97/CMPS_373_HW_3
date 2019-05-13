/**
 * @file World.h
 * @author Joey Damico
 * @date May 6, 2019
 * @brief Header file for the World class
 *
 * CMPS 373 - Object Oriented Programming
 * Homework #3 - Roadrunners & Coyotes Simulator
 *
 * This class controls the entire simulation, and stores the 2D vector for the board. It also controls each simulation
 * step and keeps track of both agent types populaitons
 */

#include "Coordinate.h"
#include "Agent.h"

#include <vector>

#ifndef World_h
#define World_h

class World {
public:
    World(int x, int y, int coyote, int roadrunner);
    void set_board(std::vector<std::vector<Agent*> > board);
    void simulation_step();
    bool check_all_agents();
    bool check_empty();
    void count_pop();
    void reset_move_all_agents();
    void fill_board();
    Coordinate generate_random_coord(int max_x, int max_y);
    int pick_random_agent();
    Agent * find_agent_by_id(int find_id);
    Coordinate get_agent_coordinate(int agt_id);
    void print_board();
    void create_board(int width, int height);
    
    int get_step_counter();
    void inc_step_counter();
    
    int get_coyote_pop();
    void set_coyote_pop(int nValue);
    int get_roadrunner_pop();
    void set_roadrunner_pop(int nValue);
    
    int get_init_coyote();
    int get_init_roadrunner();
    
protected:
    
private:
    int max_x;
    int max_y;
    int init_coyote;
    int init_roadrunner;
    
    int step_counter;
    
    int population_coyote;
    int population_roadrunner;
    
    std::vector<std::vector<Agent*> > board;
};
#endif /* World_h */
