/**
 * @file main.cpp
 * @author Joey Damico
 * @date May 6, 2019
 * @brief This is the main .cpp file CMPS-373 Homework #3
 *
 * CMPS 373 - Object Oriented Programming
 * Homework #3 - Roadrunners & Coyotes Simulator
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "World.h"
#include "Agent.h"
#include "Coyote.h"
#include "Roadrunner.h"
#include "Coordinate.h"

#define MAX_X 1
#define MAX_Y 10
#define RUNNER_COUNT 1
#define COYOTE_COUNT 2


int main(int argc, const char *argv[]) {
    // Used to create Random Numbers
    srand(time(NULL));
    
    // Stores the input from the config file
    int board_width = 0;
    int board_height = 0;
    int num_of_roadrunner = 0;
    int num_of_coyote = 0;
    
    // Used For Reading in from the Config File
    std::string buffer;
    std::string short_buffer;
    
    // Open the File
    std::ifstream config_file;
    config_file.open("config.txt");
    
    // Check if the file is open
    if(config_file.is_open()) {
        while (!config_file.eof()) {
            getline(config_file, buffer);
            
            if (buffer.substr(0, buffer.find("=")) == "WIDTH OF THE BOARD ") {
                short_buffer = buffer.substr(buffer.find("=") + 2, buffer.size());
                if (short_buffer == "") {
                    board_width = 0;
                }
                else {
                    board_width = std::stoi(short_buffer);
                }
            }
            else if (buffer.substr(0, buffer.find("=")) == "HEIGHT OF THE BOARD ") {
                short_buffer = buffer.substr(buffer.find("=") + 2, buffer.size());
                if (short_buffer == "") {
                    board_height = 0;
                }
                else {
                    board_height = std::stoi(short_buffer);
                }
            }
            else if (buffer.substr(0, buffer.find("=")) == "INITIAL NUMBER OF COYOTES ") {
                short_buffer = buffer.substr(buffer.find("=") + 2, buffer.size());
                if (short_buffer == "") {
                    num_of_coyote = 0;
                }
                else {
                    num_of_coyote = std::stoi(short_buffer);
                }
            }
            else if (buffer.substr(0, buffer.find("=")) == "INITIAL NUMBERS OF ROADRUNNERS ") {
                short_buffer = buffer.substr(buffer.find("=") + 2, buffer.size());
                if (short_buffer == "") {
                    num_of_roadrunner = 0;
                }
                else {
                    num_of_roadrunner = std::stoi(short_buffer);
                }
            }
        }
    }
    // File is not opened, close the program
    else {
        std::cerr << std::endl << "**ERROR** 'config.txt' Does Not Exist" << std::endl;
        std::cerr << "Closing The Program" << std::endl;
        return 0;
    }
    
    
    // Validate All Input
    // Check board_height
    if (board_height <= 0 || board_height > INT_MAX) {
        std::cerr << "**ERROR** Board Height input is not a valid number" << std::endl;
        std::cerr << "Closing The Program" << std::endl;
        return 0;
    }
    // Check board_width
    if (board_width <= 0 || board_width > INT_MAX) {
        std::cerr << "**ERROR** Board Width input is not a valid number" << std::endl;
        std::cerr << "Closing The Program" << std::endl;
        return 0;
    }
    // Check number of coyotes
    if (num_of_coyote <= 0 || num_of_coyote > INT_MAX) {
        std::cerr << "**ERROR** Coyote input is not a valid number" << std::endl;
        std::cerr << "Closing The Program" << std::endl;
        return 0;
    }
    // Check number of roadrunner
    if (num_of_roadrunner <= 0 || num_of_roadrunner > INT_MAX) {
        std::cerr << "**ERROR** Roadrunner input is not a valid number" << std::endl;
        std::cerr << "Closing The Program" << std::endl;
        return 0;
    }
    
    
    if (num_of_roadrunner + num_of_coyote > board_height * board_width) {
        std::cerr << "**ERROR** The number of Agent's is greater than the number of loactions in the board" << std::endl;
        std::cerr << "Closing The Program" << std::endl;
        return 0;
    }
    
    
    
    // ofstream to write to a file for each time step summary
    std::ofstream outputfile;
    // Open the file
    outputfile.open("simulation_output.txt");
    
    World world = World(board_width, board_height, num_of_roadrunner, num_of_coyote);
    
    world.create_board(board_width, board_height);
    
    world.fill_board();
    
    while(true) {
        world.count_pop();
        
        outputfile << "Simulation Step: " << world.get_step_counter() << std::endl;
        outputfile << "Roadrunner Population = " << world.get_roadrunner_pop() << std::endl;
        outputfile << "Coyote Population = " << world.get_coyote_pop() << std::endl;
        outputfile << std::endl << std::endl;
        
        if (world.get_roadrunner_pop() == 0 || world.get_coyote_pop() == 0) {
            break;
        }
        
        world.simulation_step();
    }
    
    outputfile.close();
    
    std::cout << "Simulation Over" << std::endl;
    return 0;
}
