
#ifndef Battleship_AI_h
#define Battleship_AI_h

#include "Gameboard.h"
#include <stdlib.h>

//checks the board for a hit, if there is no hit present, returns false
bool hitPresent(Board Board) {
    bool present = false;
    for (int i = 0; i < Board.nSize; i++) {
        for (int j = 0; j < Board.nSize; j++) {
            //checks for it being shot at, not part of a sunk ship and not and empty space
            if (Board.getValue(i, j) > 1 && Board.getValue(i, j) != 13 && Board.getValue(i, j) % 2 != 0) {
                present = true;
            }
        }
    }
    return present;
}

//Checks to see any point is surrounded by other points that have already been fired at.
bool surroundedHit(int row, int col, Board Board) {
    bool isSurrounded;
    int aroundCount = 0;
    int shotCount = 0;
    int rowPlus = row + 1;
    int rowMinus = row - 1;
    int colPlus = col + 1;
    int colMinus = col - 1;
    //counts the spaces around the point and compares it to the number of spaces that has be shot at
    if (colMinus >= 0) {
        aroundCount++;
        if (Board.checkIfShot(row, colMinus)) {
            shotCount++;
        }
    }
    if (colPlus < Board.nSize) {
        aroundCount++;
        if (Board.checkIfShot(row, colPlus)) {
            shotCount++;
        }
    }
    if (rowMinus >= 0) {
        aroundCount++;
        if (Board.checkIfShot(rowMinus, col)) {
            shotCount++;
        }
    }
    if (rowPlus < Board.nSize) {
        aroundCount++;
        if (Board.checkIfShot(rowPlus, col)) {
            shotCount++;
        }
    }
    if (aroundCount - shotCount == 0) {
        isSurrounded = true;
    }
    else {
        isSurrounded = false;
    }
    return isSurrounded;
}

//Looks for the first hit it can find on the gameboard
void findHit(int &row, int &col, Board Board) {
    int hitRow;
    int hitCol;
    for (int i = 0; i < Board.nSize; i++) {
        for (int j = 0; j < Board.nSize; j++) {
            //checks for it being shot at, not part of a sunk ship and not and empty space
            if (Board.checkIfShot(i, j)) {
                if (Board.getValue(i, j) != 1 && Board.getValue(i, j) != 13) {
                    //If the hit is not surrounded, then we have a guess we can make next to the hit, if not it moves to the next hit
                    if (!surroundedHit(i, j, Board)) {
                        hitRow = i;
                        hitCol = j;
                        goto finish;
                    }
                }
            }
        }
    }
    finish:
        row = hitRow;
        col = hitCol;
    
}
//Randomly guesses a row and col on the board
void getGuessEasy(int &row, int &col, Board Board) {
    row = rand() % Board.nSize;
    col = rand() % Board.nSize;
}

//Guesses in either of the 4 points around a location that is already deemed a hit
void getGuessMod(int &row, int &col, Board Board) {
    int direction;
    int value;
    if (hitPresent(Board)) { // there is already a hit
        //finds a hit on the board, also checks that the point is not already surrounded by guessed points
        findHit(row, col, Board);
        direction = rand() % 2;
        value = rand() % 2;
        //randomly picks a new point either up/down or right/left to the findHit point
        if (direction == 0) {
            if (value == 0) {
                if (row > 0) {
                    row--;
                }
                else {
                    getGuessMod(row, col, Board);
                }
            }
            else {
                if (row < Board.nSize - 1) {
                    row++;
                }
                else {
                    getGuessMod(row, col, Board);
                }
            }
        }
        else {
            if (value == 0) {
                if (col > 0) {
                    col--;
                }
                else {
                    getGuessMod(row, col, Board);
                }
            }
            else {
                if (col < Board.nSize - 1) {
                    col++;
                }
                else {
                    getGuessMod(row, col, Board);
                }
            }
        }
    }
    else {
        row = rand() % Board.nSize;
        col = rand() % Board.nSize;
    }
}

//Searches for a hit that is next to a previous hit and in the same direction as the hit
void getGuessHard(int &row, int &col, Board Board, int count) {
    if (hitPresent(Board)) { // there is already a hit
        //finds a hit on the board, also checks that the point is not already surrounded by guessed points
        findHit(row, col, Board);
        int moves;
        //looks to find a hit next to the hit point
        if (count < 50 && ((row > 0 && Board.checkIfHit(row - 1, col)) || (row < (Board.nSize - 1) && Board.checkIfHit(row + 1, col)))) {
            //Goes North/South
            if (row == 0) {
                moves = 1;
            }
            else if (row == Board.nSize - 1) {
                moves = 0;
            }
            else {
                moves = rand() % 2; // randomly picks to go either N or S
            }
            if (moves == 0) {
                while (row > 0 && Board.checkIfHit(row, col)) {
                    row--;
                }
            }
            else {
                while (row < Board.nSize - 1 && Board.checkIfHit(row, col)) {
                    row++;
                }
            }
        }
        else if (count < 50 && ((col > 0 && Board.checkIfHit(row, col - 1)) || (col < (Board.nSize - 1) && Board.checkIfHit(row, col + 1)))) {
            //Goes East/West
            if (col == 0) {
                moves = 1;
            }
            else if (col == Board.nSize - 1) {
                moves = 0;
            }
            else {
                moves = rand() % 2; // randomly picks to go either E or W
            }
            if (moves == 0) {
                count = 0;
                while (col > 0 && Board.checkIfHit(row, col)) {
                    col--;
                }
            }
            else {
                while (col < Board.nSize - 1 && Board.checkIfHit(row, col) ) {
                    col++;
                }
            }
        }
        else {
            getGuessMod(row, col, Board);
        }
    }
    else {
        row = rand() % Board.nSize;
        col = rand() % Board.nSize;
    }
}

//calls the guess getting method, depending on the input difficulty called by gameplay
void getShot(int &row_guess, int &col_guess, Board Board, int diff, int count) {
    if (diff == 1) {
        getGuessEasy(row_guess, col_guess, Board);
    }
    else if (diff == 2) {
        getGuessMod(row_guess, col_guess, Board);
    }
    else {
        getGuessHard(row_guess, col_guess, Board, count);
    }
}


#endif
