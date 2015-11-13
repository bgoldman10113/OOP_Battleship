
#include "Gameplay.h"


using namespace std;

/*
 This is the main method for the Battleship game.  All of the main menu inputs are handled here, such as the number of players, player information, difficulty as well as the option to simulate a game and play again if desired.
 */



int main()
{
    srand(static_cast<int>(time(0)));
    // take in the user's name
    string player1_name;
    cout << "Please enter your name: ";
    cin >> player1_name;
    cout << endl;
    
    // Print Menu #1
mainmenu:
    cout << "Ready to play Battleship, " << player1_name << "? Please choose an option:" << endl;
    cout << "\t1. 1-Player" << endl;
    cout << "\t2. 2-Player" << endl;
    cout << "\t3. Help" << endl;
    cout << "\t4. Simulator" << endl;
    cout << "\t5. Exit" << endl;
    cout << endl;
    
    // chose to use char so you avoid issue of infinite loop when reading in a char when program expects an int
    char option;
    cout << "Option: ";
    
input:
    cin >> option;
    cin.clear();
    cin.ignore(10000, '\n');
    
    
    /* OPTION 1: PLAY AGAINST THE AI */
    if(option == '1')
    {
        char chDifficulty = 0;
        cout << "Okay, " << player1_name << ", what difficulty would you like?" << endl;
        cout << "Enter 1 for Easy, 2 for Moderate, or 3 for Hard (Ctr-C to Quit): ";
        cin >> chDifficulty;
        cin.clear();
        cin.ignore(10000, '\n');
        while (chDifficulty < 49 || chDifficulty > 51) {
            cout << "Error please enter difficulty level between 1 and 3 (Ctr-C to Quit): ";
            cin >> chDifficulty;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        int difficulty = (int)(chDifficulty - '0');
        
        
        //the computers name is "The computer"
        gameplay(player1_name, "The Computer", difficulty, false, false);
        char playagain = 'Y';
        while ((playagain == 'Y'|| playagain == 'Y' || playagain == 'n' || playagain == 'N')) {
            cout << "Would you like to play again? (Enter Y or N) (Ctr-C to Quit): ";
            cin >> playagain;
            cin.clear();
            cin.ignore(10000, '\n');
            if (playagain == 'y' || playagain == 'Y') {
                goto mainmenu;
            }
            else if (playagain == 'n' || playagain == 'N') {
                return 0;
            }
            else {
                cout << "Invalid input, please try again. (Ctr-C to Quit)" << endl;
                cin >> playagain;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
    
    /* OPTION 2: PLAY ANOTHER PLAYER */
    else if(option == '2')
    {
        string player2_name;	// take in the second player's name
        
        cout << "Enter Player 2's Name: ";
        cin >> player2_name;
        
        //default diff = 3 so we have the right board size
        
        gameplay(player1_name, player2_name , 3 , true, false);
        char playagain;
        while ((playagain != 'Y'|| playagain != 'Y' || playagain != 'n' || playagain != 'N')) {//count < 1000 && (playagain == 'Y'|| playagain == 'Y' || playagain == 'n' || playagain == 'N')) {
            cout << "Would you like to play again? (Enter Y or N) (Ctr-C to Quit)" << endl;
            cin >> playagain;
            cin.clear();
            cin.ignore(10000, '\n');
            
            if (playagain == 'y' || playagain == 'Y') {
                goto mainmenu;
            }
            else if (playagain == 'n' || playagain == 'N') {
                return 0;
            }
            else {
                cout << "Invalid input, please try again by entering Y or N. (Ctr-C to Quit) ";
                
            }
        }
    }
    
    /* OPTION 3: HELP THE USER */
    else if(option == '3')
    {
        // Provide user help. This explains the game options
        cout << "\tHi, " << player1_name << "! Not sure what choice to make?" << endl;
        cout << "\t\tOption 1 allows you to play against the computer." << endl;
        cout << "\t\tYou will select a difficulty that will change the strategy of the AI." << endl;
        cout << "\t\tOption 2 allows you to play against another player." << endl;
        cout << "\t\tYou and a friend can create your Battleship layout and will alternate turns" << endl;
        cout << "\t\ttrying to sink each other's ships." << endl;
		cout << "\t\tTo quit at any point throughout the game, press 'Ctr-C'. Note: data will not save." << endl;
        cout << "\tGot it? Enter '1' to go back to the main menu: ";
        
        char help_choice;
        cin >> help_choice;
        cin.clear();
        cin.ignore(10000, '\n');
        
        // if the user enters 1, send the user back to the main menu
        if (help_choice == '1')
            goto mainmenu;
        else
        {
            cout << "Error. Please enter '1' to go back to the main menu. (Ctr-C to Quit) ";	// basic error handling
            cin >> help_choice;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    /* OPTION 4: SIMULATOR */
    else if(option == '4')
    {
        char chDifficulty = 0;
        cout << "Okay, " << player1_name << ", what difficulty would you like? (Ctr-C any point to Quit)" << endl;
        cout << "Enter 1 for Easy, 2 for Moderate, or 3 for Hard: ";
        cin >> chDifficulty;
        cin.clear();
        cin.ignore(10000, '\n');
        while (chDifficulty < 49 || chDifficulty > 51) {
            cout << "Error please enter difficulty level between 1 and 3" <<endl;
            cin >> chDifficulty;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        int difficulty = (int)(chDifficulty - '0');
        gameplay("First Player", "Second Player", difficulty, false, true);
        char playagain = 'Y';
        while ((playagain == 'Y'|| playagain == 'Y' || playagain == 'n' || playagain == 'N')) {
            cout << "Would you like to simulate again? (Y/N)" << endl;
            cin >> playagain;
            cin.clear();
            cin.ignore(10000, '\n');
            if (playagain == 'y' || playagain == 'Y') {
                goto mainmenu;
            }
            else if (playagain == 'n' || playagain == 'N') {
                return 0;
            }
            else {
                cout << "Invalid input, please try again." << endl;
                cin >> playagain;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
    
    /* OPTION 5: EXIT GAME */
    else if (option == '5')
    {
        char exit;
    quit:
        cout << player1_name << ", are you sure you want to exit this game? Game data will not be saved.";
        cout << "Enter Y or N: ";
        cin >> exit;
        cin.clear();
        cin.ignore(10000, '\n');
        
        // if the user enters N, don't quit the game, instead take them to main menu
        if(exit == 'N' || exit == 'n')
        {
            goto mainmenu;
        }
        
        // if the user enters Y, break from the program
        else if(exit == 'Y' || exit == 'y')
            return(0);
        else
        {
            cout << "Invalid choice. Please enter Y or N: ";
            goto quit;
        }
    }
    
    else
    {
        cout << "Invalid entry, please enter another option: ";	// basic error handling
        goto input;
    }
}
