/**
 * @file Coyote.cpp
 * @author Joey Damico
 * @date May 6, 2019
 * @brief Main cpp file for the Coyote Class, this class inheirts from the Agent class
 *
 * CMPS 373 - Object Oriented Programming
 * Homework #3 - Roadrunners & Coyotes Simulator
 */

#include <vector>

#include "Agent.h"
#include "Coyote.h"

#include <iostream>



/**
 * Constructor for the Coyote Class
 *
 * @param nId -> The Id for the instance of the Coyote Class
 */
Coyote::Coyote(int nId) {
    this->agent_id = nId;
}


/**
 * Prints the type agent to the screen
 */
void Coyote::print_kind() {
    std::cout << "C";
}


/**
 * Returns the kind of Agent it is
 */
std::string Coyote::get_kind() {
    return "C";
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
void Coyote::move(std::vector<std::vector<Agent*> > &board, int coyote_current_pop, int coyote_init_pop, int roadrunner_current_pop, int roadrunner_init_pop) {
    Coordinate current_location = this->get_location();
    
    if (this->check_if_dead()) {
        board[current_location.x][current_location.y] = NULL;
        delete this;
        return;
    }
    if (this->check_can_breed(board)) {
        Coordinate new_location = this->find_new_coordinate(board, current_location, false);
        board[new_location.x][new_location.y] = new Coyote(coyote_current_pop + coyote_init_pop + 1);
        board[new_location.x][new_location.y]->set_coords(new_location.x, new_location.y);
    }
    else {
        this->inc_die_counter();
        current_location = this->get_location();
        Coordinate new_location = this->find_new_coordinate(board, current_location, true);
        board[current_location.x][current_location.y] = NULL;
        this->set_coords(new_location.x, new_location.y);
        board[new_location.x][new_location.y] = this;
    }
}


/**
 * Looks for Roadrunners around the coyote, if one is found returns the location that Roadrunner is in
 *
 * @param board -> The simulation board
 *
 * @return [Coordinate] The location of the Roadrunner to be Eaten
 */
Coordinate Coyote::find_roadrunner(std::vector<std::vector<Agent*> > board) {
    Coordinate roadrunner_location;
    
    // Check Up
    if (this->agent_location.y - 1 != -1) {
        if (board[this->agent_location.x][this->agent_location.y - 1] != NULL) {
            if (board[this->agent_location.x][this->agent_location.y - 1]->get_kind() == "R") {
                roadrunner_location.x = this->agent_location.x;
                roadrunner_location.y = this->agent_location.y - 1;
                return roadrunner_location;
            }
        }
    }
    // Check Down
    if (this->agent_location.y + 1 < board[1].size()) {
        if (board[this->agent_location.x][this->agent_location.y + 1] != NULL) {
            if (board[this->agent_location.x][this->agent_location.y + 1]->get_kind() == "R") {
                roadrunner_location.x = this->agent_location.x;
                roadrunner_location.y = this->agent_location.y + 1;
                return roadrunner_location;
            }
        }
    }
    // Check Right
    if (this->agent_location.x + 1 < board.size()) {
        if (board[this->agent_location.x + 1][this->agent_location.y] != NULL) {
            if (board[this->agent_location.x + 1][this->agent_location.y]->get_kind() == "R") {
                roadrunner_location.x = this->agent_location.x + 1;
                roadrunner_location.y = this->agent_location.y;
                return roadrunner_location;
            }
        }
    }
    // Check Left
    if (this->agent_location.x - 1 != -1) {
        if (board[this->agent_location.x - 1][this->agent_location.y] != NULL) {
            if (board[this->agent_location.x - 1][this->agent_location.y]->get_kind() == "R") {
                roadrunner_location.x = this->agent_location.x - 1;
                roadrunner_location.y = this->agent_location.y;
                return roadrunner_location;
            }
        }
    }
    
    roadrunner_location.x = -1;
    roadrunner_location.y = -1;
    return roadrunner_location;
}


/**
 * Returns the new coordinate that the coyote should move too, even if that it is to eat a roadrunner
 *
 * @param board -> The simulation board
 * @param current_location -> The current location that the Coyote is at now
 *
 * @return [Coordinate] The location to move the Coyote too
 */
Coordinate Coyote::find_new_coordinate(std::vector<std::vector<Agent*> > board, Coordinate current_location, bool look_for_roadrunner) {
    Coordinate new_location;
    
    if (look_for_roadrunner) {
        Coordinate roadrunner_location = board[current_location.x][current_location.y]->find_roadrunner(board);
        // Check For Roadrunner
        if (roadrunner_location.x != -1 && roadrunner_location.y != -1) {
            board[roadrunner_location.x][roadrunner_location.y] = NULL;
            this->reset_die_counter();
            return roadrunner_location;
        }
    }
    // No Roadrunner
    else {
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
        // Check left
        if (current_location.x - 1 != -1) {
            if (board[current_location.x - 1][current_location.y] == NULL) {
                new_location.x = current_location.x - 1;
                new_location.y = current_location.y;
                return new_location;
            }
        }
        return current_location;
    }
    return current_location;
}


/**
 * Increases the counter since the last time the Coyote has eaten
 */
void Coyote::inc_die_counter() {
    this->counter_die = this->counter_die + 1;
}


/**
 * Resets the counter since the last time the Coyote has eaten to 0
 */
void Coyote::reset_die_counter() {
    this->counter_die = 0;
}


/**
 * Returns the counter since the last time the Coyote has eaten
 */
int Coyote::get_die_counter() {
    return this->counter_die;
}


/**
 * Check is the Coyote is dead
 *
 * @return [bool] True if the Coyote is dead, False if not
 */
bool Coyote::check_if_dead() {
    if (get_die_counter() >= this->STARVE) {
        return true;
    }
    
    return false;
}


/**
 * Increasing the Breed Counter by one, after each time the Coyote moves
 */
void Coyote::inc_breed_counter() {
    this->counter_breed = this->counter_breed + 1;
}


/**
 * Reset the Breed Counter to zero, after each time the Coyote as Breed
 */
void Coyote::reset_breed_counter() {
    this->counter_breed = 0;
}


/**
 * Returns the current value of the Coyotes Breed counter
 *
 * @return [int] The current value of the breed counter
 */
int Coyote::get_breed_counter() {
    return this->counter_breed;
}


/**
 * Checks if the Coyote can breed. It checks if it has moved enough times to be able to breed, it also checks if there is an
 * empty location next to the Coyote to place to the new Coyote
 *
 * @param board -> The 2D vector of the board, to see if there is an open space around it
 *
 * @return [bool] True if the coyote can breed, false if it can
 */
bool Coyote::check_can_breed(std::vector<std::vector<Agent*> > board) {
    // Check if the Coyote has moved enough steps
    if (get_die_counter() >= 8) {
        // Get it's current location
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
    
    // Coyote cannot breed
    return false;
}
