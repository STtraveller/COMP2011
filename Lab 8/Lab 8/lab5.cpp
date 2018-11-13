/*
 * lab5.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: kevinw
 */


#include "header.h"


//This function is to print the map. The first parameter is a 2D array that represents the
//map. The second parameter check if it is in the debug mode.
void printMap(const char map[][WIDTH], bool debug) {
    cout << " ";
    for (int i = 0; i < WIDTH; i++) {
        cout << " " << i ;
    }
    cout << endl;
    
    for (int i = 0; i < HEIGHT; i++) {
        cout << i << " ";
        
        for (int j = 0; j < WIDTH; j++) {
            if (!debug && map[i][j] == SHIP)
                cout << EMPTY << " ";
            else
                cout << map[i][j] << " ";
        }
        
        cout << endl;
    }
}

// Place a ship of a particular size on the map.
// Make sure that the battle ships cannot overlap with each other, nor can
// they be placed out of the game board.
// You need to randomly place them on the board.
// You can always assume the map has enough room to place the battle ship when the function is being called.
void placeShip(char map[][WIDTH], int size) {
    //add your code here
    while (true) {
        int startCol = rand() % WIDTH;
        int startRow = rand() % HEIGHT;
        bool isHorizontal = rand() % 2;
        bool valid = true;
        
        if (isHorizontal)
        {
            if (size + startCol > WIDTH)
                valid = false;
            else
            {
                for (int i = startCol; i < size + startCol; i++)
                    if (map[startRow][i] == SHIP)
                    {
                        valid = false;
                        break;
                    }
            }
            
            if (valid)
            {
                for (int i = startCol; i < size + startCol; i++)
                    map[startRow][i] = SHIP;
                break;
            }
        }
        else
        {
            if (size + startRow > HEIGHT)
                valid = false;
            else
            {
                for (int i = startRow; i < size + startRow; i++)
                    if (map[i][startCol] == SHIP)
                    {
                        valid = false;
                        break;
                    }
            }
            
            if (valid)
            {
                for (int i = startRow; i < size + startRow; i++)
                    map[i][startCol] = SHIP;
                break;
            }
        }
        
    }
}


// To check if a cannon hits a battleship.
// Put the correct symbol on the map and return true if  a ship is hit.
// Note: repeated firing on the hit area of an already damaged ship is
// considered as a miss and the symbol for the area should remain '*'.
bool isHit(char map[][WIDTH], int col, int row) {
    //add your code here
    if (map[row][col] == HIT)
        return false;
    
    if (map[row][col] != SHIP) {
        map[row][col] = MISS;
        return false;
    }
    map[row][col] = HIT;
    return true;
}


// It checks if the game ends. It returns true if there is no more SHIP symbol on the map.
// It returns false otherwise.
bool isGameOver(const char map[][WIDTH]) {
    //add your code here
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            if (map[i][j] == SHIP)
                return false;
    
    return true;
}
