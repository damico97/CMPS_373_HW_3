/**
 * @file World.h
 * @author Joey Damico
 * @date May 6, 2019
 * @brief Main cpp file for the World class
 *
 * CMPS 373 - Object Oriented Programming
 * Homework #3 - Roadrunners & Coyotes Simulator
 *
 * This class controls the entire simulation, and stores the 2D vector for the board. It also controls each simulation
 * step and keeps track of both agent types populaitons
 */

#include "World.h"

#include <iostream>
#include <iomanip>

#include "Agent.h"
#include "Coyote.h"
#include "Roadrunner.h"
#include "Coordinate.h"


/**
 * Constructor for the World class, sets some of the memeber variables
 *
 * @param x -> The width of the board
 * @param y -> The height of the board
 * @param coyote -> The initial count of coyotes on the board
 * @param roadrunner -> The initial count of roadrunners on the board
 */
World::World(int x, int y, int roadrunner, int coyote) {
    this->max_x = x;
    this->max_y = y;
    this->init_coyote = coyote;
    this->init_roadrunner = roadrunner;
    
    this->step_counter = 0;
    
    this->population_coyote = 0;
    this->population_roadrunner = 0;
}


/**
 * Takes in a 2D vector for the board and assigns it to the board member variable
 *
 * @param board -> The 2D vector for the board
 */
void World::set_board(std::vector<std::vector<Agent*> > board) {
    this->board = board;
}


/**
 * This function runs a single simulation step, making sure all the agents have either moved, breed or died.
 * before moving finishing the step
 */
void World::simulation_step() {
    int test_id;
    
    //std::cout << std::endl << "***  Start Step  ***" << std::endl << std::endl;
    
    // Make sure not all of one kind has died
    while (get_roadrunner_pop() != 0 || get_coyote_pop() != 0) {
        // Get a random Agent's ID
        test_id = pick_random_agent();
        
        // Check if the we did not get an agent ID
        if (test_id == -100) {
            // No ID exit loop
            break;
        }
        
        // Find the Agent, and call it's Move() function
        find_agent_by_id(test_id)->move(board, get_coyote_pop(), get_init_coyote(), get_roadrunner_pop(), get_init_roadrunner());
        
        //print_board();
    }
    // Recount the Current Population of both types of Agents
    count_pop();
    // Reset all the moved bool for the next simulation step
    reset_move_all_agents();
    // Increase the Step Counter
    inc_step_counter();
    
    //std::cout << std::endl << "***  End Step  ***" << std::endl << std::endl;
}


/**
 * Goes through the board and makes sure all the agents have moved, returns false if an agent has not moved, and true if all have moved
 *
 * @return [bool] True if all agents have moved, False if not
 */
bool World::check_all_agents() {
    // Loop through the Rows
    for (int i = 0; i < this->board.size(); i++) {
        // Loop through the Columns
        for (int j = 0; j < this->board[i].size(); j++) {
            // Check if the location is occupied
            if (this->board[i][j] != NULL) {
                // Check if the Agent has moved
                if (!this->board[i][j]->checked_moved()) {
                    return false;
                }
            }
        }
    }
    
    // All Agent's have moved
    return true;
}


/**
 * Goes through the entire board too check if there are no agents left in the board
 *
 * @return [bool] True if the board is empty, False if the board still contains Agents
 */
bool World::check_empty() {
    // Loop through Rows
    for (int i = 0; i < this->board.size(); i++) {
        // Loop through Columns
        for (int j = 0; j < this->board[i].size(); j++) {
            // Check if the location is empty
            if (this->board[i][j] != NULL) {
                // Agent Found, board is not Empty
                return false;
            }
        }
    }
    
    // No Agents found, The board is empty
    return true;
}


/**
 * Counts up the Population of both kind of Agents
 */
void World::count_pop() {
    // Set both populations to 0
    set_roadrunner_pop(0);
    set_coyote_pop(0);
    
    // Local int's to store count
    int roadrunner = 0;
    int coyote = 0;
    
    // Loop throught the Rows
    for (int i = 0; i < this->board.size(); i++) {
        // Loop through the Columns
        for (int j = 0; j < this->board[i].size(); j++) {
            // Check if the Location is Empty
            if (this->board[i][j] != NULL) {
                // Check if the Agent is a Roadrunner
                if (this->board[i][j]->get_kind() == "R") {
                    roadrunner++;
                }
                // Check if the Agent is a Coyote
                else if (this->board[i][j]->get_kind() == "C") {
                    coyote++;
                }
            }
        }
    }
    
    // Set both population member variables
    set_coyote_pop(coyote);
    set_roadrunner_pop(roadrunner);
}


/**
 * Goes through all the agents that are on the board, and set's the moved bool back to false for the next simulation step
 */
void World::reset_move_all_agents() {
    // Loop through the Rows
    for (int i = 0; i < this->board.size(); i++) {
        // Loop through the Columns
        for (int j = 0; j < this->board[i].size(); j++) {
            // Check if the location is Empty
            if (this->board[i][j] != NULL) {
                this->board[i][j]->reset_moved();
            }
        }
    }
}


/**
 * Fills it with the coyotes and roadrunners, addes the amount of agents that are given when the World Class is created
 */
void World::fill_board() {
    int count = 0;
    
    // Fill with Roadrunners
    while (count < this->init_roadrunner) {
        // Generate random location
        Coordinate nCoord = generate_random_coord(this->max_x, this->max_y);
        if (this->board[nCoord.x][nCoord.y] == NULL) {
            this->board[nCoord.x][nCoord.y] = new Roadrunner(100 + count);
            this->board[nCoord.x][nCoord.y]->set_coords(nCoord.x, nCoord.y);
            count++;
        }
        else {
            // Do Nothing
        }
    }
    // Set the roadrunner population count
    this->population_roadrunner = count;
    
    // Fill with Coyotes
    count = 0;
    while (count < this->init_coyote) {
        Coordinate nCoord = generate_random_coord(this->max_x, this->max_y);
        if (this->board[nCoord.x][nCoord.y] == NULL) {
            this->board[nCoord.x][nCoord.y] = new Coyote(200 + count);
            this->board[nCoord.x][nCoord.y]->set_coords(nCoord.x, nCoord.y);
            count++;
        }
        else {
            // Do Nothing
        }
    }
    // Set the coyote population count
    this->population_coyote = count;
}


/**
 * Creates a random location within the board
 *
 * @param max_x -> The largest width possible
 * @param max_y -> The largest height possible
 *
 * @return [Coordinate] The location that was randomly generated
 */
Coordinate World::generate_random_coord(int max_x, int max_y) {
    Coordinate nCoord;
    nCoord.x = rand() % max_x;
    nCoord.y = rand() % max_y;
    
    return nCoord;
}


/**
 * Picks a random Agent from the simulation board
 *
 * @return [int] The id of the Agent that was selected randomly
 */
int World::pick_random_agent() {
    int agt_id = -1;
    Coordinate nCoord;
    
    int count = 0;
    // Loop for as many locations that exist
    while(count <= this->max_x * this->max_y) {
        // Generate a random location from the board
        nCoord = generate_random_coord(this->max_x, this->max_y);
        // Check if that location is occupied
        if (this->board[nCoord.x][nCoord.y] != NULL) {
            // Check if the Agent has moved
            if (!this->board[nCoord.x][nCoord.y]->checked_moved()) {
                // If an Agent exists there get it's ID
                agt_id = board[nCoord.x][nCoord.y]->get_agent_id();
                this->board[nCoord.x][nCoord.y]->set_moved();
                return agt_id;
            }
        }
        count++;
    }
    
    // The board must be empty
    return -100;
}


/**
 * Looks for the Agent in the game board, by using the Agent's ID, if no Agent is found with the ID given, NULL is returned
 *
 * @return [Agent *] A pointer to the Agent in the board, If NO Agent found returns NULL
 */
Agent * World::find_agent_by_id(int find_id) {
    // Loop through all the rows of the board
    for (int i = 0; i < this->board.size(); i++) {
        // Loop through all the columns of the board
        for (int j = 0; j < this->board[i].size(); j++) {
            // Check if the location is not empty
            // Check if Agent at the location has the ID that we are looking for
            if (this->board[i][j] != NULL && this->board[i][j]->get_agent_id() == find_id) {
                // Agent found, return that Agent
                return this->board[i][j];
            }
        }
    }
    
    // No Agent found with that ID, return NULL
    return NULL;
}


/**
 * Function takes in a Agent's ID and returns the Coordinate of where that agent is located on the board
 *
 * @param agt_id -> The ID of the Agent to find the location of
 *
 * @return [Coordinate] The the location of the Agent
 */
Coordinate World::get_agent_coordinate(int agt_id) {
    // Find the Agent in the board
    // Returns it's location using the 'get_location()' function that is part of the Agent Class
    return find_agent_by_id(agt_id)->get_location();
}


/**
 * Function will just delay the board to the screen
 */
void World::print_board() {
    // Prints top row of '-' to the correct size for the width of the board
    std::cout << std::endl << std::setfill('-') << std::setw(7 * board[1].size()) << "" << std::endl;
    // Loop through the rows
    for (int i = 0; i < this->board.size(); i++) {
        // Loop through the columns
        for (int j = 0; j < this->board[i].size(); j++) {
            // If the location has a Agent
            if (this->board[i][j] != NULL) {
                // Prints the Agent type
                std::cout << "|  ";
                this->board[i][j]->print_kind();
                std::cout << "  |";
            }
            // If the location does not have an Agent
            else {
                // Print a blank space
                std::cout << "|     |";
            }
        }
        // Prints a row of '-' to the corroect size for the width of the board
        std::cout << std::endl << std::setfill('-') << std::setw(7 * board[i].size()) << "" << std::endl;
    }
    std::cout << std::endl;
}


/**
 * This function will create a 2D vector that will store all the agents in the simulation, the board vector is created to the
 * width and height that are passed as parameters, and all location are initalized to NULL
 *
 * @param width -> The width of the board
 * @param height -> The height of the board
 */
void World::create_board(int width, int height) {
    // Create the board vector
    std::vector<std::vector<Agent*> > nBoard;
    
    // Loop for as many columns that are requested
    for (int i = 0; i < width; i++) {
        // Resize the vector to hold that many columns
        nBoard.resize(width);
        // Loop for as many rows that are requested
        for (int j = 0; j < height; j++) {
            // push_back NULL into each location
            nBoard[i].push_back(NULL);
        }
    }
    
    // Return the fully created board
    set_board(nBoard);
}


/**
 * Returns the simulation step counter
 *
 * @return [int] the current simulation step
 */
int World::get_step_counter() {
    return this->step_counter;
}


/**
 * Increases the simulation counter by one
 */
void World::inc_step_counter() {
    this->step_counter = this->step_counter + 1;
}


/**
 * Returns the current Coyote Population
 *
 * @return [int] Current Coyote Count
 */
int World::get_coyote_pop() {
    return this->population_coyote;
}


/**
 * Set the coyote population to the value passed as a parameter
 *
 * @param nValue -> The new coyote count
 */
void World::set_coyote_pop(int nValue) {
    this->population_coyote = nValue;
}


/**
 * Returns the current Roadrunner Population
 *
 * @return [int] Current Roadrunner Population
 */
int World::get_roadrunner_pop() {
    return this->population_roadrunner;
}


/**
 * Sets the roadrunner population to the value passed as a parameter
 *
 * @param nValue -> The new roadrunner count
 */
void World::set_roadrunner_pop(int nValue) {
    this->population_roadrunner = nValue;
}


/**
 * Returns the initial count of Coyotes from the begining of the simulation
 *
 * @return [int] The initial Coyote Population
 */
int World::get_init_coyote() {
    return this->init_coyote;
}


/**
 * Returns teh initial count of Roadrunners from the begining of the simulation
 *
 * @return [int] The initial Roadrunner Populaiton
 */
int World::get_init_roadrunner() {
    return this->init_roadrunner;
}
