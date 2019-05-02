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
#include <stdlib.h>
#include <time.h>

#include "Agent.h"
#include "Coyote.h"
#include "Roadrunner.h"

#define MAX_X 10
#define MAX_Y 10
#define RUNNER_COUNT 20
#define CYOTE_COUNT 15

struct Coordinate {
    int x;
    int y;
};

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
    
    Agent * test = find_agent_by_id(200 + coyote_count - 2, board);
    
    std::cout << std::endl;
    test->print_agent();
    std::cout << "  Location: " << test->get_x_coord() << ", " << test->get_y_coord();
    std::cout << std::endl;
    
    print_board(board);
    
    

    
    return 0;
}
