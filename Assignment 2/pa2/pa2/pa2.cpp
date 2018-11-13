//  pa2.cpp
//	minesweeper

#include "definition.h"

/* ATTENTION:
 * 1. PLEASE Read the introduction before each function carefully!
 * 2. You can ONLY add your code where you find a comment:
 *   // complete your code here
 * 3. DO NOT modify other things!!
 */

/************* Functions Requires You to Complete. *************/

/* ================================================================
 * Randomly place mines and flowers on the  play board.
 * mine and flower should not exist in the same cell.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - num_mines: number of mines;
 * - num_flowers: number of flowers;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * ----------------------------------------------------------------
 */
void generateMineAndFlower(Cell cell[MAXSIZE][MAXSIZE], int num_mines,
                           int num_flowers, int height, int width, int firstrow, int firstcol) {

	cout << "\nPlacing mines and flowers ......" << endl;

	// complete your code here
    int row, col;
    for (int i = 0; i < num_mines; i++) {
        do {
            row = rand() % height;
            col = rand() % width;
        } while(!isEmpty(cell, row, col) || (row == firstrow && col == firstcol));
        cell[row][col].content = MINE;
    }
    for (int i = 0; i < num_flowers; i++) {
        do {
            row = rand() % height;
            col = rand() % width;
        } while(!isEmpty(cell, row, col));
        cell[row][col].content = FLOWER;
    }
}

/* ================================================================
 * Count the number of surrounding mines of all cells on the game board.
 * You should compute this number not just for empty cells,
 * but also the mine cells and flower cells.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * ----------------------------------------------------------------
 */
void generateMinecountMap(Cell cell[MAXSIZE][MAXSIZE], int height,
	                      int width) {

	cout << "\ngenerate real maps ......" << endl;

	// complete your code here
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int count = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (isOnBoard(row + i, col + j, height, width)) {
                        if (cell[row + i][col + j].content == MINE) {
                            count++;
                        }
                    }
                }
            }
            cell[row][col].count = count;
        }
    }
}

/* ================================================================
 * Sweep the empty cell recursively.
 * You are REQUIRED to implement this function using recursion.
 * You will receive NO mark if your implementation is not an recursion.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - row: index of current row;
 * - col: index of current column;
 * Output:
 * - additional_life: how many additional lives are obtained
 * ----------------------------------------------------------------
 */
int recursiveSweep(Cell cell[MAXSIZE][MAXSIZE], int height, int width,
	               int row, int col) {

	// complete your code here
    int additional_life = 0;
    if (cell[row][col].count == 0) {
        cell[row][col].swept = true;
        if (cell[row][col].content == FLOWER) {
            cout << "Congratulations! You got an additional life!\n";
            additional_life++;
        }
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (isOnBoard(row + i, col + j, height, width) && (i != 0 || j != 0) && !cell[row + i][col + j].swept && !cell[row + i][col + j].marked) {
                    additional_life += recursiveSweep(cell, height, width, row + i, col + j);
                }
            }
        }
    } else {
        cell[row][col].swept = true;
        if (cell[row][col].content == FLOWER) {
            cout << "Congratulations! You got an additional life!\n";
            return 1;
        } else {
            return 0;
        }
    }
    return additional_life;
}

/* ================================================================
 * Run the game according to the operation chosen
 * ATTENTION:
 * 1. you will use recursiveSweep() in this function.
 * 2. you will use isOnBoard() to help validate the input.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - row: index of current row;
 * - col: index of current column;
 * - life: record number of lives remaining;
 * - num_mines: number of mines;
 * - num_marked_mines: number of mines marked as mine by player;
 * - op: operation taken. { 0: sweep; 1: mark; 2: unmark}
 * ----------------------------------------------------------------
 */
void operation(Cell cell[MAXSIZE][MAXSIZE], int height, int width,
	           int row , int col, int& life, int num_mines,
	           int& num_marked_mines, int op) {

	/* choose to sweep */
	if (op == 0) {

		// complete your code here
        while (cell[row][col].marked || !isOnBoard(row, col, height, width)) {
            if (!isOnBoard(row, col, height, width)) {
                cout << "The cell should be the one which is on the board. row[0, " << height - 1 << "] col[0, " << width - 1 << "]\n";
            } else if (cell[row][col].marked) {
                cout << "The cell should be the one which is not marked.\n";
            }
            cout << "which cell in the map: row col?" << endl;
            cin >> row >> col;
        }
        if (cell[row][col].content == MINE) {
            life--;
            cell[row][col].swept = true;
            cell[row][col].marked = true;
            num_marked_mines++;
        } else if (!cell[row][col].swept) {
            life += recursiveSweep(cell, height, width, row, col);
        } else {
            int surrounding_marked = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (isOnBoard(row + i, col + j, height, width) && cell[row + i][col + j].marked) {
                        surrounding_marked++;
                    }
                }
            }
            if (surrounding_marked == cell[row][col].count) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (!cell[row + i][col + j].swept && !cell[row + i][col + j].marked) {
                            life += recursiveSweep(cell, height, width, row + i, col + j);
                        }
                    }
                }
            }
        }
	}

	/* choose to mark */
	if (op == 1) {

	 	// complete your code here
        if (num_marked_mines >= num_mines) {
            cout << "WARNING: You've already marked 10 mines!!\nTo mark this one, first unmark a marked mine!!\n";
            return;
        }
        while (cell[row][col].swept || cell[row][col].marked || !isOnBoard(row, col, height, width)) {
            if (!isOnBoard(row, col, height, width)) {
                cout << "The cell should be the one which is on the board. row[0, " << height - 1 << "] col[0, " << width - 1 << "]\n";
            } else if (cell[row][col].marked) {
                cout << "The cell should be the one which is not marked.\n";
            } else if (cell[row][col].swept) {
                cout << "The cell should be the one which is not swept.\n";
            }
            cout << "which cell in the map: row col?" << endl;
            cin >> row >> col;
        }
        cell[row][col].marked = true;
        num_marked_mines++;
        if (cell[row][col].content == FLOWER) {
            cout << "Ooooops!! This is a FLOWER!! You lose a chance to have an additional life!!";
            cell[row][col].marked = false;
            cell[row][col].swept = true;
            num_marked_mines--;
        }
	}


	/* choose to unmark */
	if (op == 2) {

		// complete your code here
        if (num_marked_mines == 0) {
            cout << "WARNING: No cell is marked now!\n";
            return;
        }
        bool possible_to_unmark = false;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (cell[row][col].marked && !cell[row][col].swept) {
                    possible_to_unmark = true;
                    break;
                }
            }
            if (possible_to_unmark) {
                break;
            }
        }
        if (!possible_to_unmark) {
            cout << "WARNING: No possible cell to unmark!\n";
            return;
        }
        while (!cell[row][col].marked || !isOnBoard(row, col, height, width) || cell[row][col].swept) {
            if (!isOnBoard(row, col, height, width)) {
                cout << "The cell should be the one which is on the board. row[0, " << height - 1 << "] col[0, " << width - 1 << "]\n";
            } else if (!cell[row][col].marked) {
                cout << "The cell should be the one which is marked.\n";
            } else if (cell[row][col].swept) {
                cout << "Cannot unmark swept mine.\n";
            }
            cout << "which cell in the map: row col?" << endl;
            cin >> row >> col;
        }
        cell[row][col].marked = false;
        num_marked_mines--;
	}
}

/* ================================================================
 * Check game state: win/lose/continue
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - num_mines: number of mines;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - life: record number of lives remaining;
 * Output:
 * - {return -1: lose; return 0: continue; return 1: win}
 * ----------------------------------------------------------------
 */
int checkWin(const Cell cell[MAXSIZE][MAXSIZE], int num_mines,
             int height, int width, int life) {

	// complete your code here
    if (life == 0) {
        return -1;
    } else {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                if (cell[row][col].content != MINE && !cell[row][col].swept) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
