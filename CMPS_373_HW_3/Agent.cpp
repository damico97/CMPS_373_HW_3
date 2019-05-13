/**
 * @file Agent.cpp
 * @author Joey Damico
 * @date May 6, 2019
 * @brief The main agent class file
 *
 * CMPS 373 - Object Oriented Programming
 * Homework #3 - Roadrunners & Coyotes Simulator
 */

#include "Agent.h"

#include <iostream>


/**
 * Default constructor for the Agent Class
 */
Agent::Agent() {
    this->agent_id = NULL;
    this->counter_breed = 0;
    this->counter_die = 0;
    this->moved = false;
}


/**
 * Constructor for the Agent class that takes an ID for the agent as a parameter
 *
 * @param nId -> The id for the Agent
 */
Agent::Agent(int nId) {
    this->agent_id = nId;
    this->counter_breed = 0;
    this->counter_die = 0;
}


/**
 * sets the bool that says the agent has made a move
 */
void Agent::set_moved() {
    if (!this->moved) {
        this->moved = true;
    }
    else {
        std::cerr << "** ERROR! ** Agent set_moved()" << std::endl;
    }
}


/**
 * resets the bool move value to false
 */
void Agent::reset_moved() {
    this->moved = false;
}


/**
 * Returns the bool move value
 */
bool Agent::checked_moved() {
    return this->moved;
}


/**
 * Sets the location reference for the agents
 *
 * @param x -> The x location
 * @param y -> The y location
 */
void Agent::set_coords(int x, int y) {
    this->agent_location.x = x;
    this->agent_location.y = y;
}


/**
 * Returns the Coordinate that the Agent is located in
 *
 * @return [Coordinate] The agent's location
 */
Coordinate Agent::get_location() {
    return this->agent_location;
}


/**
 * Returns the ID of the agent
 *
 * @return [int] The ID of the agent
 */
int Agent::get_agent_id() {
    return this->agent_id;
}


/**
 * Prints the Agent's ID
 */
void Agent::print_agent() {
    std::cout << this->agent_id;
}
