/*
 *
 * will need to make two board objects (one for P1 and one for either P2 or AI)
 * 	and will need to keep track of which one you are manipulating for each turn.
 *
 * Can reference extraneous methods to put in other files such as ships.
 * 	then we can make this call on methods in ships (i.e. checkIfSunk)
 *
 *
 *
 * Methods you can call from this class:
 * 	void setBoard(); 
 *      sets each of the boards and sets all values in that board to 0
 *  void setShip(int row, int col, int shiptype);
 *      takes in the ship value and changes that location to that ship value (to be called multiple times per each ship)
 *  int getValue(int row, int col);
 *      returns the value on the board for a specific location
 *  bool checkIfShot(int row, int col);
 *      returns whether or not that point has been fired at or not
 *  bool checkIfHit(int row, int col);
 *      returns whether or not that point has been fired at or not as well as whether or not is was a hit
 *  void changeToHit(int row, int col);
 *      changes the value at a given location to hit by adding 1 to the board value
 *  void changeToSunk(int row, int col);
 *      changes the value at a given location to sunk by changing the board value to 13
 *  void printShips();
 *      prints where the ships are located on the board
 *  void printGameBoard();
 *      prints the hits and misses on the board
 *  void printTwoShipBoards(Board second);
 *      prints two ship boards side by side
 *  void printTwoGameBoards(Board second);
 *      prints two gameboards side by side
 *
 *
 */


#ifndef Battleship_Gameboard_h
#define Battleship_Gameboard_h
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class Board
{
public:
    int nSize;
    //the max size the board will ever be
    int maxSize = 9;
    Board(int size);
    Board();
    //declares the array to be used to store the board values
    int** gameboard = new int* [maxSize];
    
    //Methods
    void setBoard();
    void setShip(int row, int col, int shiptype);
    int getValue(int row, int col);
    bool checkIfShot(int row, int col);
    bool checkIfHit(int row, int col);
    void changeToHit(int row, int col);
    void changeToSunk(int row, int col);
    void printShips();
    void printGameBoard();
    void printTwoShipBoards(Board second);
    void printTwoGameBoards(Board second);
    
};

Board::Board(int size) {
    nSize = size;
    for (int i = 0; i < nSize; i++)
        gameboard[i] = new int[nSize];
    setBoard();
    
}

Board::Board() {
    gameboard = NULL;
}

void Board::setBoard()
{
    for (int i = 0; i < nSize; i++) {
        for (int j = 0; j < nSize; j++) {
            gameboard[i][j] = 0;
        }
    }
}

void Board::setShip(int row, int col, int shiptype) {
    gameboard[row][col] = shiptype;
}

//get value method
int Board::getValue(int row, int col)
{
    return gameboard[row][col];
}

//checks if spot has already been shot at for gameplay to check on for turns
bool Board::checkIfShot(int row, int col)
{
    if(row < 0 || row >= nSize || col < 0 || col >= nSize) {
        return false;
    }
    else if(gameboard[row][col] % 2 == 0)
    {
        return false;
    }
    else return true;
}

bool Board::checkIfHit(int row, int col)
{
    if(row < 0 || row >= nSize || col < 0 || col >= nSize) {
        return false;
    }
    else if(gameboard[row][col] % 2 == 0 || gameboard[row][col] == 1 || gameboard[row][col] == 13)
    {
        return false;
    }
    else return true;
}

void Board::changeToHit(int row, int col)
{
    gameboard[row][col]++;
    if(gameboard[row][col] == 1)
    {
        cout << "Miss";
    }
    else if(gameboard[row][col] == 3)
    {
        cout << "Hit!";
    }
    else if(gameboard[row][col] == 5)
    {
        cout << "Hit!";
    }
    else if(gameboard[row][col] == 7)
    {
        cout << "Hit!";
    }
    else if(gameboard[row][col] == 9)
    {
        cout << "Hit!";
    }
    else if(gameboard[row][col] == 11)
    {
        cout << "Hit!";
    }
    
}

void Board::changeToSunk(int row, int col)
{
    gameboard[row][col] = 13;
    
}

void Board::printTwoShipBoards(Board second)
{
    int counter = 1;
    int counter2 = 1;
    
    cout << "\n";
    for(int i = 0; i < nSize + 1; ++i)
    {
        if (i != 0) {
            cout << i << "  ";
        }
        else {
            cout << "   ";
        }
    }
    cout << "		";
    for(int i = 0; i < nSize + 1; ++i)
    {
        if (i != 0) {
            cout << i << "  ";
        }
        else {
            cout << "   ";
        }
    }
    cout << "\n";
    for(int row = 0; row < nSize; ++row)
    {
        cout << counter++ << "  ";
        for(int col = 0; col < nSize; ++col)
        {
            if(gameboard[row][col] == 0)
            {
                cout << "~";
            }
            else if(gameboard[row][col] == 1)
            {
                cout << "O";
            }
            else if(gameboard[row][col] == 2)
            {
                cout << "P";
            }
            else if(gameboard[row][col] == 4)
            {
                cout << "D";
            }
            else if(gameboard[row][col] == 6)
            {
                cout << "S";
            }
            else if(gameboard[row][col] == 8)
            {
                cout << "B";
            }
            else if(gameboard[row][col] == 10)
            {
                cout << "C";
            }
            else
            {
                cout << "X";
            }
            cout << "  ";
        }
        cout << "		";
        //second board
        cout << counter2++ << "  ";
        for(int col = 0; col < nSize; ++col)
        {
            if(second.getValue(row, col) == 0)
            {
                cout << "~";
            }
            else if(second.getValue(row, col) == 1)
            {
                cout << "O";
            }
            else if(second.getValue(row, col) == 2)
            {
                cout << "P";
            }
            else if(second.getValue(row, col) == 4)
            {
                cout << "D";
            }
            else if(second.getValue(row, col) == 6)
            {
                cout << "S";
            }
            else if(second.getValue(row, col) == 8)
            {
                cout << "B";
            }
            else if(second.getValue(row, col) == 10)
            {
                cout << "C";
            }
            else
            {
                cout << "X";
            }
            cout << "  ";
        }
        //goes down a line when the row is finished
        cout << "\n";
    }
}

void Board::printTwoGameBoards(Board second)
{
    int counter = 1;
    int counter2 = 1;
    
    cout << "\n";
    for(int i = 0; i < nSize + 1; ++i)
    {
        if (i != 0) {
            cout << i << "  ";
        }
        else {
            cout << "   ";
        }
    }
    cout << "		";
    for(int i = 0; i < nSize + 1; ++i)
    {
        if (i != 0) {
            cout << i << "  ";
        }
        else {
            cout << "   ";
        }
    }
    cout << "\n";
    for(int row = 0; row < nSize; ++row)
    {
        cout << counter++ << "  ";
        for(int col = 0; col < nSize; ++col)
        {
            if(gameboard[row][col] % 2 == 0)
            {
                cout << "~";
            }
            else if(gameboard[row][col] == 1)
            {
                cout << "O";
            }
            else
            {
                cout << "X";
            }
            cout << "  ";
        }
        cout << "		";
        //second board
        cout << counter2++ << "  ";
        for(int col = 0; col < nSize; ++col)
        {
            if(second.getValue(row, col) % 2 == 0)
            {
                cout << "~";
            }
            else if(second.getValue(row, col) == 1)
            {
                cout << "O";
            }
            else
            {
                cout << "X";
            }
            cout << "  ";
        }
        //goes down a line when the row is finished
        cout << "\n";
    }
}


void Board::printShips()
{
    int counter = 1;
    cout << "\n";
    for(int i = 0; i < nSize + 1; ++i)
    {
        if (i != 0) {
            cout << i << "  ";
        }
        else {
            cout << "   ";
        }
    }
    cout << "\n";
    for(int row = 0; row < nSize; ++row)
    {
        cout << counter++ << "  ";
        for(int col = 0; col < nSize; ++col)
        {
            if(gameboard[row][col] == 0)
            {
                cout << "~";
            }
            else if(gameboard[row][col] == 1)
            {
                cout << "O";
            }
            else if(gameboard[row][col] == 2)
            {
                cout << "P";
            }
            else if(gameboard[row][col] == 4)
            {
                cout << "D";
            }
            else if(gameboard[row][col] == 6)
            {
                cout << "S";
            }
            else if(gameboard[row][col] == 8)
            {
                cout << "B";
            }
            else if(gameboard[row][col] == 10)
            {
                cout << "C";
            }
            else
            {
                cout << "X";
            }
            cout << "  ";
        }
        //goes down a line when the row is finished
        cout << "\n";
    }
}

//printing ship board
void Board::printGameBoard()
{
    int counter = 1;
    cout << "\n";
    for(int i = 0; i < nSize + 1; ++i)
    {
        if (i != 0) {
            cout << i << "  ";
        }
        else {
            cout << "   ";
        }
    }
    cout << "\n";
    for(int i = 0; i < nSize; ++i)
    {
        cout << counter++ << "  ";
        for(int j = 0; j < nSize; ++j)
        {
            if (gameboard[i][j]%2 == 0) {
                cout << "~" << "  ";
            }
            else if (gameboard[i][j] == 1) {
                cout << "O" << "  ";
            }
            else {
                cout << "X" << "  ";
            }
        }
        //goes down a line when the row is finished
        cout << "\n";
    }
}


#endif
