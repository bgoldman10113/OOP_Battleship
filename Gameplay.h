/*GAMEPLAY.H
 */

#ifndef Battleship_Gameplay_h
#define Battleship_Gameplay_h

#include "Gameboard.h"
#include "AI.h"
#include "Ships.h"
#include <unistd.h>


//This methods checks that the position of the ship (either randomly assigned or placed by user) is in a vlid location and is not already taken up by another ship or outside of the board
bool checkPosition(int row, int col, int direction, int shipSize, Board Board) {
    bool isCorrect = false;
    if (direction == 0) {
        if (row + shipSize >= Board.nSize) {
            return false;
        }
        for (int i = 0; i < shipSize; i++) {
            if (Board.getValue(row, col) != 0) {
                return false;
            }
            row++;
        }
    }
    else if (direction == 1) {
        if (col + shipSize >= Board.nSize) {
            return false;
        }
        for (int i = 0; i < shipSize; i++) {
            if (Board.getValue(row, col) != 0) {
                return false;
            }
            col++;
        }
    }
    isCorrect = true;
    return isCorrect;
}

//Places the ships randomly onto the board so the user does not have to place them manually
void placeShipRandom(shipStruct ship, Board &Board) { //Takes in a reference of the board so that is can alter the values
    int row = 0;
    int col = 0;
    bool isGood = false;
    int direction = 0;
    while (!isGood) {
        row = rand() % Board.nSize;
        col = rand() % Board.nSize;
        direction = rand() % 2;
        isGood = checkPosition(row, col, direction, ship.length, Board);
    }
    for (int i = 0; i < ship.length; i++) {
        Board.setShip(row, col, ship.shipValue);
        if (direction == 0) {
            row++;
        }
        else {
            col++;
        }
    }
    
}

//Allows the user to choose the location of where his/her ships would be located
void placeShipUser(shipStruct ship, Board &Board) { //Takes in a reference of the board so that is can alter the values
    char chRow = 0;
    char chCol = 0;
    char chDirection = 0;
    int row = 0;
    int col = 0;
    bool isGood = false;
    int direction = 0;
    while (!isGood) {
        //Prints out the board after each ship is placed so that the user knows where their ships already are to assist in placing
        Board.printShips();
        cout << "Place the starting coordinates of your " << ship.name << " (Ship length is " << ship.length << ")" << endl;
        cout << "Enter a row between 1 and " << Board.nSize << endl;
        cin >> chRow;
        cin.clear();
        cin.ignore(10000, '\n');
        chRow--;
        while (chRow < 48 || chRow > Board.nSize + '0' - 1) {
            cout << "Error please enter a number between 1 and " << Board.nSize << "." << endl;
            cin >> chRow;
            cin.clear();
            cin.ignore(10000, '\n');
            chRow--;
        }
        row = (int)(chRow - '0');
        
        
        cout << "Enter a col between 1 and " << Board.nSize << endl;
        cin >> chCol;
        cin.clear();
        cin.ignore(10000, '\n');
        chCol--;
        while (chCol < 48 || chCol > Board.nSize + '0' - 1) {
            cout << "Error please enter a number between 1 and " << Board.nSize << "." << endl;
            cin >> chCol;
            cin.clear();
            cin.ignore(10000, '\n');
            chCol--;
        }
        col = (int)(chCol - '0');
        
        //Asks user to determine whether the ship should be North/South or East/West
        cout << "Choose the orientation of the ship (1 for vertical, 2 for horizontal): " << endl;
        cin >> chDirection;
        cin.clear();
        cin.ignore(10000, '\n');
        chDirection--;
        while (chDirection < 48 || chDirection > 49) {
            cout << "Error please enter a number between 1 and 2." << endl;
            cin >> chDirection;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        direction = (int)(chDirection - '0');
        
        isGood = checkPosition(row, col, direction, ship.length, Board);
        if (!isGood) {
            cout << "Invalid location please try again." << endl;
        }
    }
    for (int i = 0; i < ship.length; i++) {
        Board.setShip(row, col, ship.shipValue);
        if (direction == 0) {
            row++;
        }
        else {
            col++;
        }
    }
    
}
//This places the ships onto the board randomly or from user input
void placeShips(Board &Board, bool isRandom, int difficulty, bool AI) { //Takes in a reference of the board so that is can alter the values
    
    //Uses the shipStruct to declare the types of ships we are using, their size and there ship value
    struct shipStruct ships[5];
    ships[0].name = "Patrol Boat";
    ships[0].shipValue = 2;
    ships[0].length = 2;
    ships[1].name = "Destroyer";
    ships[1].shipValue = 4;
    ships[1].length = 3;
    ships[2].name = "Submarine";
    ships[2].shipValue = 6;
    ships[2].length = 3;
    ships[3].name = "Battleship";
    ships[3].shipValue = 8;
    ships[3].length = 4;
    ships[4].name = "Carrier Ship";
    ships[4].shipValue = 10;
    ships[4].length = 5;
    
    //This is called if it is multiplayer, the computer is placing the ships, or the user does not want to enter their ships manually
    if (isRandom) {
        placeShipRandom(ships[0], Board);
        placeShipRandom(ships[1], Board);
        placeShipRandom(ships[2], Board);
        //The higher the difficulty, the more ships are places onto the board
        if(difficulty==2 || difficulty==3 || !AI) placeShipRandom(ships[3], Board);
        if (difficulty == 3|| !AI) placeShipRandom(ships[4], Board);
    }
    //This is only called when the user chooses to enter their ships manually
    else {
        placeShipUser(ships[0], Board);
        placeShipUser(ships[1], Board);
        placeShipUser(ships[2], Board);
        //The higher the difficulty, the more ships are places onto the board
        if (difficulty == 2 || difficulty == 3) placeShipUser(ships[3], Board);
        if (difficulty == 3) placeShipUser(ships[4], Board);
    }
}

/*	The playersturn method allows for the game to take in the player's requested location they want to
	shoot at. If the game is two player, this method is called for each player. By guessing a row and
	col, the user has the ability to sink the ship. When coordinated are recieved, the data is sent to
	check if hit or check if miss.
 */
void checkIfSunk(Board &Board) { //Takes in a reference of the board so that is can alter the values
    //This method checks the boad after each round and determines whether or not any ships were sunk that round
    //If there were sunk, it changes the ship values to 13, which is the "sunk value"
    int patrolCount = 2;
    int destroyerCount = 3;
    int submarineCount = 3;
    int battleshipCount = 4;
    int carrierCount = 5;
    for (int i = 0; i < Board.nSize; i++) {
        for (int j = 0; j < Board.nSize; j++) {
            if (Board.getValue(i, j) == 3) {
                patrolCount--;
            }
            else if (Board.getValue(i, j) == 5) {
                destroyerCount--;
            }
            else if (Board.getValue(i, j) == 7) {
                submarineCount--;
            }
            else if (Board.getValue(i, j) == 9) {
                battleshipCount--;
            }
            else if (Board.getValue(i, j) == 11) {
                carrierCount--;
            }
        }
    }
    //Output so that the user knows they have sunk a ship
    if (patrolCount == 0) {
         cout << "You've sunk the Patrol Boat." << endl;
    }
    else if (destroyerCount == 0) {
        cout << "You've sunk the Destroyer." << endl;
    }
    else if (submarineCount == 0) {
        cout << "You've sunk the Submarine." << endl;
    }
    else if (battleshipCount == 0) {
        cout << "You've sunk the Battleship." << endl;
    }
    else if (carrierCount == 0) {
        cout << "You've sunk the Carrier." << endl;
    }
    //changing the ships to sunk value
    for (int i = 0; i < Board.nSize; i++) {
        for (int j = 0; j < Board.nSize; j++) {
            if (Board.getValue(i, j) == 3) {
                if (patrolCount == 0) {
                    Board.changeToSunk(i, j);
                }
            }
            else if (Board.getValue(i, j) == 5) {
                if (destroyerCount == 0) {
                    Board.changeToSunk(i, j);
                }
            }
            else if (Board.getValue(i, j) == 7) {
                if (submarineCount == 0) {
                    Board.changeToSunk(i, j);
                }
            }
            else if (Board.getValue(i, j) == 9) {
                if (battleshipCount == 0) {
                    Board.changeToSunk(i, j);
                }
            }
            else if (Board.getValue(i, j) == 11) {
                if (carrierCount == 0) {
                    Board.changeToSunk(i, j);
                }
            }
        }
    }
}

bool checkIfWon(Board Board) {
    //Checks the board each round to determine whether or not all the ships have been sunk
    //This counts the number of sunk ships and adds it to the number of spots where no ship is present
    //If that value is equal to the total number of spaces on the board, the user wins
    
    int sunkCount = 0;
    int missCount = 0;
    bool isWinner;
    for (int i = 0; i < Board.nSize; i++) {
        for (int j = 0; j < Board.nSize; j++) {
            if (Board.getValue(i, j) == 13) {
                sunkCount++;
            }
            else if (Board.getValue(i, j) == 0 || Board.getValue(i, j) == 1) {
                missCount++;
            }
        }
    }
    if ((sunkCount + missCount) == (Board.nSize*Board.nSize)) {
        isWinner = true;
    }
    else {
        isWinner = false;
    }
    return isWinner;
}


// this is called everytime it is a players turn
void playersturn(string pName, Board &Board) {		//Takes in a reference of the board so that is can alter the values
    char chRow = 0;
    char chCol = 0;
    int row_guess = -1;
    int col_guess = -1;
    bool isRowGood = false;
    bool isColGood = false;
    char Continue;
    cout << "\n";
    cout << pName << "'s Turn. Enter any letter to continue." << endl;
    cin >> Continue;
    cout << "----- "<< pName << "'s Battle Board. -----" << endl;
    //prints out the players gameboard
    Board.printGameBoard();
    cout << pName << "'s Turn: \nGuess a Row: ";
    while (!isRowGood) {
        cin >> chRow;cin.clear();
        cin.ignore(10000, '\n');
        chRow--;
        while (chRow < 48 || chRow > Board.nSize + '0' - 1) {
            cout << "Error please enter number between 1 and " << Board.nSize << ": ";
            cin >> chRow;
            cin.clear();
            cin.ignore(10000, '\n');
            chRow--;
        }
        row_guess = (int)chRow - '0';
        if (row_guess >= 0 && row_guess < Board.nSize) {
            isRowGood = true;
        }
        else {
            cout << "Invalid guess, please guess between 1 and " << Board.nSize  << "." << "\nGuess a Row:";
            isRowGood = false;
        }
    }
    cout << "Guess a Column: ";
    while (!isColGood) {
        cin >> chCol;
        cin.clear();
        cin.ignore(10000, '\n');
        chCol--;
        while (chCol < 48 || chCol > Board.nSize + '0' - 1) {
            cout << "Error please enter number between 1 and " << Board.nSize << ": ";
            cin >> chCol;
            cin.clear();
            cin.ignore(10000, '\n');
            chCol--;
        }
        col_guess = (int)chCol - '0';
        if (col_guess >= 0 && col_guess < Board.nSize) {
            isColGood = true;
        }
        else {
            cout << "Invalid guess, please guess between 1 and " << Board.nSize << "\nGuess a Column: ";
            isColGood = false;
        }
    }
    
    //checks if the guess is already shot at
    if (!Board.checkIfShot(row_guess, col_guess)) {
        cout << "Firing..." << endl;
        usleep(1500000);
        Board.changeToHit(row_guess, col_guess);
        Board.printGameBoard();
    }
    else {
        cout << "\nOops! You've already fired here! Guess again: ";
        playersturn(pName, Board);
    }
    
}

/*	Similarly to the playersturn method, the computersturn method takes in the AI's coordinate choices that are handled
	in the AI.h file.
 */

void computersturn(string computerName, Board &Board, int diff) { //Takes in a reference of the board so that is can alter the values
    int row_guess;
    int col_guess;
    cout << "----- " << computerName << "'s Battle Board. -----" << endl;
    //prints out the players shipboard
    Board.printGameBoard();
    cout << "Hmmmm let me think..." << endl;
    usleep(1500000);
    getShot(row_guess, col_guess, Board, diff, 0);
    //this will outsput the row and col for the computer to shoot at, and the checkIfShot will be done inside the getShot method
    //right now its only going to guess a random int between 0 and 4
    //}
    //checks if the guess is already shot at, still needs a way to check for an invalid location (out of bounds or even a string
    if (!Board.checkIfShot(row_guess, col_guess)) {
        cout << "I guess (" << row_guess + 1 << ", " << col_guess + 1 << ")." << endl;
        usleep(1500000);
        Board.changeToHit(row_guess, col_guess);
        cout << endl;
        usleep(200000);
        Board.printGameBoard();
    }
    else {
        computersturn(computerName, Board,diff);
    }
}

/*	The gameplay method keeps a running tally of whose turn it is. Each instance of the game increases the turnCount, and the if
	statement allows the program to know that an odd number represents player1's turn and an even number represents either player2
	or the computer AI.
 */

void gameplay(string p1Name, string p2Name, int diff, bool multiPlayer, bool simulate) {
    int turnCount = 1;
  /****************************TWO PLAYERS****************************/
    if(multiPlayer) {
        //Default board size for multiplayer is 9x9, so we coult either call this with the boardsize here, or imput a default difficulty everytime it is multiplayer
        int boardSize = 9;
        //declares the two boards
        Board Board1(boardSize);
        Board Board2(boardSize);
        //since multiplayer, this would randomly place ships
        placeShips(Board1, multiPlayer, 3, false);
        placeShips(Board2, multiPlayer, 3, false);
        
        cout << "STARTING TWO PLAYER WAR!!!" << endl;
        usleep(1000000);
        
        while (turnCount <= 2*Board1.nSize * Board1.nSize) {
            cout << "\n------ " << p1Name <<"'s Board ------" << "      " << " ------ " << p2Name <<"'s Board" << " ------" << endl;
            Board1.printTwoGameBoards(Board2);
            //Here begins the first players turn, since it is an odd turn number
            if (turnCount%2 != 0) {
                playersturn(p1Name, Board2);
                checkIfSunk(Board2);
                if (checkIfWon(Board2)) {
                    cout << "Gameover! " << p1Name << " Won!" << endl;
                    break;
                }
                turnCount++;
            }
            else {
                //Here begins the first players turn, since it is an even turn number
                playersturn(p2Name, Board1);
                checkIfSunk(Board1);
                if (checkIfWon(Board1)) {
                    cout << "Gameover! " << p2Name << " Won!" << endl;
                    break;
                }
                turnCount++;
            }
        }
    }
    
    /****************************ONE PLAYER****************************/
    else {
        
        if (!simulate) {
            int boardSize;
            if (diff == 1) {			// playing the computer at easy setting
                boardSize = 5;
            }
            else if (diff == 2) {		// playing the computer at med setting
                boardSize = 7;
            }
            else {
                boardSize = 9;			// playing the computer at hard setting
            }
            Board Board1(boardSize);
            Board Board2(boardSize);
            char chManualPlace;
            int manualPlace;
            cout << "Would you like to place your own ships, or have them randomly placed for you? (Enter 1 for placing them yourself, 2 for random)" << endl;
            
            cin >> chManualPlace;
            cin.clear();
            cin.ignore(10000, '\n');
            while (chManualPlace < 49 || chManualPlace > 50) {
                cout << "Error please enter either 1 or 2." << endl;
                cin >> chManualPlace;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            manualPlace = (int)chManualPlace - '0';
            if (manualPlace == 1) {
                placeShips(Board1, multiPlayer, diff, false);
            }
            else {
                placeShips(Board1, true, diff, true);
            }
            placeShips(Board2, true, diff, true);//Sends the Board, and 2 trues; 1st true tells it that its randomly placed and 2nd true tells it to account for difficulty)
            
            cout << "STARTING ONE PLAYER WAR!!!" << endl;
            usleep(1000000);
            
            // this statement handles keeping track of whose turn it is
            while (turnCount <= 2*Board1.nSize * Board1.nSize) {
                
                if (turnCount%2 != 0) {					// if turnCount is odd, it's player1's turn
                    cout << "\n----- YOUR SHOTS FIRED -----" << endl;
                    Board2.printGameBoard();
                    cout << "----- YOUR SHIPS LOCATION -----" << endl;
                    Board1.printShips();
                    playersturn(p1Name, Board2);
                    checkIfSunk(Board2);
                    if (checkIfWon(Board2)) {
                        cout << "Gameover! " << p1Name << " Won!" << endl;
                        break;
                    }
                    turnCount++;
                }
                else {									// if turnCount is even, it's computer's turn
                    char Continue;
                    cout << "\n";
                    cout << p2Name << "'s Turn. Enter any letter to continue." << endl;
                    cin >> Continue;
                    computersturn(p2Name, Board1, diff);
                    checkIfSunk(Board1);
                    if (checkIfWon(Board1)) {
                        cout << "Gameover! " << p2Name << " Won!" << endl;
                        break;
                    }
                    cout << "\n";
                    cout << p1Name << ", enter any letter to see your boards." << endl;
                    cin >> Continue;
                    turnCount++;
                }
            }
        }
        else {
            /****************************SIMULATOR****************************/

            int boardSize;
            if (diff == 1) {			// playing the computer at easy setting
                boardSize = 5;
            }
            else if (diff == 2) {		// playing the computer at med setting
                boardSize = 7;
            }
            else {
                boardSize = 9;			// playing the computer at hard setting
            }
            Board Board1(boardSize);
            Board Board2(boardSize);
            placeShips(Board1, true, diff, true);
            placeShips(Board2, true, diff, true);//Sends the Board, and 2 trues; 1st true tells it that its randomly placed and 2nd true tells it to account for difficulty)
            //the computer is playing itself here, therefore everything is placed randomly
            
            
            cout << "STARTING SIMULATED WAR!!!" << endl;
            usleep(1000000);
            
            
            // this statement handles keeping track of whose turn it is
            while (turnCount <= 2*Board1.nSize * Board1.nSize) {
                cout << "---- " << p1Name <<"'s Board ----" << "     " << " ---- " << p2Name <<"'s Board" << " ----" << endl;
                Board1.printTwoGameBoards(Board2);
                if (turnCount%2 != 0) {					// if turnCount is odd, it's player1's turn
                    cout << "\n" << p1Name << "'s Turn." << endl;
                    computersturn(p1Name, Board2, diff);
                    checkIfSunk(Board2);
                    if (checkIfWon(Board2)) {
                        cout << "Gameover! " << p1Name << " Won!" << endl;
                        break;
                    }
                    turnCount++;
                }
                else {									// if turnCount is even, it's computer's turn
                    cout << "\n" << p2Name << "'s Turn." << endl;
                    computersturn(p2Name, Board1, diff);
                    checkIfSunk(Board1);
                    if (checkIfWon(Board1)) {
                        cout << "Gameover! " << p2Name << " Won!" << endl;
                        break;
                    }
                    turnCount++;
                }
            }
        }
    }
    
}

#endif
