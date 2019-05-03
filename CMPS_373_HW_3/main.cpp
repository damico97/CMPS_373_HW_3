//
//  main.cpp
//  CMPS_373_HW_3
//
//  Created by Joey Damico on 5/1/19.
//  Copyright © 2019 Joey Damico. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Agent.h"
#include "Coyote.h"
#include "Roadrunner.h"
#include "Coordinate.h"

#define MAX_X 4
#define MAX_Y 4
#define RUNNER_COUNT 2
#define CYOTE_COUNT 2


Coordinate generate_random_coord(int max_x, int max_y) {
    Coordinate nCoord;
    nCoord.x = rand() % max_x;
    nCoord.y = rand() % max_y;
    
    return nCoord;
}


int pick_random_agent(std::vector<std::vector<Agent*> > board) {
    int agt_id = -1;
    Coordinate nCoord;
    while(true) {
        nCoord = generate_random_coord(MAX_X, MAX_Y);
        if (board[nCoord.x][nCoord.y] != NULL) {
            agt_id = board[nCoord.x][nCoord.y]->get_agent_id();
            break;
        }
    }
    return agt_id;
}

Agent * find_agent_by_id(int find_id, std::vector<std::vector<Agent*> > board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != NULL && board[i][j]->get_agent_id() == find_id) {
                return board[i][j];
            }
        }
    }
    return NULL;
}

Coordinate get_agent_coordinate(std::vector<std::vector<Agent*> > board, int agt_id) {
    return find_agent_by_id(agt_id, board)->get_location();
}

void print_board(std::vector<std::vector<Agent*> > board) {
    std::cout << std::endl << std::setfill('-') << std::setw(7 * board[1].size()) << "" << std::endl;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != NULL) {
                std::cout << "|  ";
                board[i][j]->print_kind();
                std::cout << "  |";
            }
            else {
                std::cout << "|     |";
            }
        }
        std::cout << std::endl << std::setfill('-') << std::setw(7 * board[i].size()) << "" << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::vector<Agent*> > create_board(int width, int height) {
    std::vector<std::vector<Agent*> > nBoard;
    for (int i = 0; i < width; i++) {
        nBoard.resize(width);
        for (int j = 0; j < height; j++) {
            nBoard[i].push_back(NULL);
        }
    }
    return nBoard;
}

Coordinate find_new_coordinate(std::vector<std::vector<Agent*> > board, Coordinate current_location, std::string type) {
    Coordinate new_location;
    
    if (type == "C" || type == "R") {
        // Check Up
        if (current_location.y - 1 != -1) {
            if (board[current_location.x][current_location.y - 1] == NULL) {
                new_location.x = current_location.x;
                new_location.y = current_location.y - 1;
                return new_location;
            }
        }
        if (current_location.y + 1 < board[1].size()) {
            if (board[current_location.x][current_location.y + 1] == NULL) {
                new_location.x = current_location.x;
                new_location.y = current_location.y + 1;
                return new_location;
            }
        }
        if (current_location.x + 1 < board.size()) {
            if (board[current_location.x + 1][current_location.y] == NULL) {
                new_location.x = current_location.x + 1;
                new_location.y = current_location.y;
                return new_location;
            }
        }
        if (current_location.x - 1 != -1) {
            if (board[current_location.x - 1][current_location.y] == NULL) {
                new_location.x = current_location.x - 1;
                new_location.y = current_location.y;
                return new_location;
            }
        }
    }
    //else if (type == "R") {
    //    return current_location;
    //}
    else {
        // Error
    }
    return current_location;
}

void move_coyote(std::vector<std::vector<Agent*> > &board, int agt_id) {
    Agent * temp = find_agent_by_id(agt_id, board);
    Coordinate current_location = get_agent_coordinate(board, agt_id);
    Coordinate new_location = find_new_coordinate(board, current_location, temp->get_kind());
    board[current_location.x][current_location.y] = NULL;
    temp->set_coords(new_location.x, new_location.y);
    board[new_location.x][new_location.y] = temp;
}


int main(int argc, const char *argv[]) {
    srand(time(NULL));
    
    int roadrunner_count = 0;
    int coyote_count = 0;
    
    std::vector<std::vector<Agent*> > board = create_board(MAX_X, MAX_Y);
    
    //print_board(board);
    
    int count = 0;
    while (count < RUNNER_COUNT) {
        Coordinate nCoord = generate_random_coord(MAX_X, MAX_Y);
        if (board[nCoord.x][nCoord.y] == NULL) {
            board[nCoord.x][nCoord.y] = new Roadrunner(100 + count);
            board[nCoord.x][nCoord.y]->set_coords(nCoord.x, nCoord.y);
            count++;
        }
        else {
            // Do Nothing
        }
    }
    roadrunner_count = count;
    
    //print_board(board);
    
    std::cout << std::endl << std:: endl;
    
    count = 0;
    while (count < CYOTE_COUNT) {
        Coordinate nCoord = generate_random_coord(MAX_X, MAX_Y);
        if (board[nCoord.x][nCoord.y] == NULL) {
            board[nCoord.x][nCoord.y] = new Coyote(200 + count);
            board[nCoord.x][nCoord.y]->set_coords(nCoord.x, nCoord.y);
            count++;
        }
        else {
            // Do Nothing
        }
    }
    
    coyote_count = count;
    
    print_board(board);
    std::cout << std::endl << std::endl << std::endl;
    
    int test_id;
    //Agent * test;
    
    while(true) {
        test_id = pick_random_agent(board);
        move_coyote(board, test_id);
        print_board(board);
        //std::cout << std::endl << std::endl << std::endl;
        //test->print_agent();
        //std::cout << "  Location: " << test->get_location().x << ", " << test->get_location().y;
        //std::cout << std::endl;
        sleep(3);
        //break;
    }
    
    return 0;
}
