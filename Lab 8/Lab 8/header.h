/*
 * header.h
 *
 *  Created on: Oct 24, 2018
 *      Author: kevinw
 */


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;
const char SHIP = 'U';
const char HIT = '*';
const char EMPTY = '.';
const char MISS = 'x';


// We can actually skip the variable names in the header file
void printMap(const char [][WIDTH], bool = true);
void placeShip(char [][WIDTH], int) ;
bool isHit(char [][WIDTH], int, int);

// Or we can have a different variable name in the cpp file
bool isGameOver(const char another_variable_name[][WIDTH]);
