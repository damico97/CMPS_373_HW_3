/**
 * @file Roadrunner.cpp
 * @author Joey Damico
 * @date May 6, 2019
 * @brief Main cpp file for the Roadrunner Class, this class inheirts from the Agent class
 *
 * CMPS 373 - Object Oriented Programming
 * Homework #3 - Roadrunners & Coyotes Simulator
 */

#include "Agent.h"
#include "Roadrunner.h"
#include "Coordinate.h"

#include <iostream>


/**
 * Constructor for the Roadrunner Class
 *
 * @param nId -> The ID for the new Roadrunner
 */
Roadrunner::Roadrunner(int nId) {
    this->agent_id = nId;
}


/**
 * Prints the kind of the Agent to the Screen, used for debugging purposes
 */
void Roadrunner::print_kind() {
    std::cout << "R";
}


/**
 * Returns a string which is the kind of the Agent, in this case it 'R' for Roadrunner
 *
 * @return [std::string] "R" for Roadrunner
 */
std::string Roadrunner::get_kind() {
    return "R";
}


/**
 * Checks if the agent is dead, if not then move the agent
 *
 * @param board -> The 2D vector simulation board
 * @param coyote_current_pop -> Current population of Coyotes <Used For Breeding New Agents>
 * @param coyote_init_pop -> Initial population of Coyotes <Used For Breeding New Agents>
 * @param roadrunner_current_pop -> Current population of Roadrunners <Used For Breeding New Agents>
 * @param roadrunner_init_pop -> Initial population of Roadrunners <Used For Breeding New Agents>
 */
void Roadrunner::move(std::vector<std::vector<Agent*> > &board, int coyote_current_pop, int coyote_init_pop, int roadrunner_current_pop, int roadrunner_init_pop) {
    Coordinate current_location = this->get_location();
    
    if (check_can_breed(board)) {
        Coordinate new_location = this->find_new_coordinate(board, current_location, false);
        board[new_location.x][new_location.y] = new Roadrunner(roadrunner_init_pop + roadrunner_current_pop + 1);
        board[new_location.x][new_location.y]->set_coords(new_location.x, new_location.y);
        this->reset_breed_counter();
    }
    else {
        Coordinate new_location = this->find_new_coordinate(board, current_location, false);
        board[current_location.x][current_location.y] = NULL;
        this->set_coords(new_location.x, new_location.y);
        this->inc_breed_counter();
        board[new_location.x][new_location.y] = this;
    }
}


/**
 * This function is only used in Coyote class but it has to be a member of the Agent class in order for it work, so it is declaired
 * here just to keep the Compiler Happy
 */
Coordinate Roadrunner::find_roadrunner(std::vector<std::vector<Agent*> > board) {
    // ****** THIS CODE WILL NEVER RUN ********
    // ****** THIS CODE WILL NEVER RUN ********
    // ****** THIS CODE WILL NEVER RUN ********
    std::cerr << "Illegal Access To Find_Roadrunner in Non Coyote Class" << std::endl;
    exit(1);
    
    Coordinate duck;
    return duck;
}


/**
 * Looks for a empty space around the Roadrunner, and returns the first open location so the Roadrunner can move to it
 *
 * @param board -> The simulation board
 * @param current_location -> The location that the Roadrunner is currently at
 * @param look_for_roadrunner -> boolen, which doesn't do anything in this class, it's for the Coyote Class
 *
 * @param [Coordinate] The location for the Roadunner to move to
 */
Coordinate Roadrunner::find_new_coordinate(std::vector<std::vector<Agent*> > board, Coordinate current_location, bool look_for_roadrunner) {
    Coordinate new_location;
    
    // Check Up
    if (current_location.y - 1 != -1) {
        if (board[current_location.x][current_location.y - 1] == NULL) {
            new_location.x = current_location.x;
            new_location.y = current_location.y - 1;
            return new_location;
        }
    }
    // Check Down
    if (current_location.y + 1 < board[1].size()) {
        if (board[current_location.x][current_location.y + 1] == NULL) {
            new_location.x = current_location.x;
            new_location.y = current_location.y + 1;
            return new_location;
        }
    }
    // Check Right
    if (current_location.x + 1 < board.size()) {
        if (board[current_location.x + 1][current_location.y] == NULL) {
            new_location.x = current_location.x + 1;
            new_location.y = current_location.y;
            return new_location;
        }
    }
    // Check Left
    if (current_location.x - 1 != -1) {
        if (board[current_location.x - 1][current_location.y] == NULL) {
            new_location.x = current_location.x - 1;
            new_location.y = current_location.y;
            return new_location;
        }
    }
    return current_location;
}


/*
 * Increases the breed counter, everytime the Roadrunner has moved
 */
void Roadrunner::inc_breed_counter() {
    this->counter_breed = this->counter_breed + 1;
}


/*
 * Resets the breed counter to 0, after the roadrunner has breed
 */
void Roadrunner::reset_breed_counter() {
    this->counter_breed = 0;
}


/*
 * Returns the Breed counter
 *
 * @return [int] the Current value of the the breed counter
 */
int Roadrunner::get_breed_counter() {
    return this->counter_breed;
}


/*
 * Checks if the Roadrunner can breed given it's current state
 *
 * @param board -> The simluation board
 * @return [bool] TRUE if the Roadrunner can breed, FALSE if it can't
 */
bool Roadrunner::check_can_breed(std::vector<std::vector<Agent*> > board) {
    if (get_breed_counter() >= BREED) {
        Coordinate current_location = this->get_location();
        // Check Up
        if (current_location.y - 1 != -1) {
            if (board[current_location.x][current_location.y - 1] == NULL) {
                return true;
            }
        }
        // Check Down
        if (current_location.y + 1 < board[1].size()) {
            if (board[current_location.x][current_location.y + 1] == NULL) {
                return true;
            }
        }
        // Check Right
        if (current_location.x + 1 < board.size()) {
            if (board[current_location.x + 1][current_location.y] == NULL) {
                return true;
            }
        }
        // Check left
        if (current_location.x - 1 != -1) {
            if (board[current_location.x - 1][current_location.y] == NULL) {
                return true;
            }
        }
    }
    
    return false;
}
