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

void print_board(std::vector<std::vector<Agent*> > board) {
    std::cout << std::endl << std::setfill('-') << std::setw(7 * board[1].size()) << "" << std::endl;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != NULL) {
                std::cout << "| ";
                board[i][j]->print_agent();
                std::cout << " |";
            }
            else {
                std::cout << "|  E  |";
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
    
    std::vector<std::vector<Agent*> > board = create_board(MAX_X, MAX_Y);
    
    //print_board(board);
    
    int count = 0;
    while (count < RUNNER_COUNT) {
        Coordinate nCoord = generate_random_coord(MAX_X, MAX_Y);
        if (board[nCoord.x][nCoord.y] == NULL) {
            board[nCoord.x][nCoord.y] = new Agent(100 + count);
            count++;
        }
        else {
            // Do Nothing
        }
    }
    
    print_board(board);
    
    std::cout << std::endl << std:: endl;
    
    count = 0;
    while (count < CYOTE_COUNT) {
        Coordinate nCoord = generate_random_coord(MAX_X, MAX_Y);
        if (board[nCoord.x][nCoord.y] == NULL) {
            board[nCoord.x][nCoord.y] = new Agent(200 + count);
            count++;
        }
        else {
            // Do Nothing
        }
    }
    
    print_board(board);

    
    return 0;
}
