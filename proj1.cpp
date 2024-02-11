/**********************************************
 ** File: proj1.cpp
 ** Project: CMSC 202 Project 1, Spring 2023
 ** Author: Joshua Hur
 ** Date: 02/24/23
 ** Section: 42
 ** E-mail: jhur1@umbc.edu
 **
 ** This is the program file for Project 1.
 ** This program provides a user with a game environment called the Balloon Surveillance Tracker.
 ** Throughout the game, the player is going to find where the randomly placed and hidden balloon on the map.
 ** Upon the player's valid input, the program can print a map of the current status and helps the player guess where the balloon is.
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 10; // number of rows of the map (X-axis).
const int COLS = 10; // number of columns of the map (Y-axis).
const int ACTUAL_ROWS = ROWS - 1; // the actual number of rows of the map since x starts from 0
const int ACTUAL_COLS = COLS - 1; // the actual number of columns of the map since y starts from 0

//---------------------------------------------
// Name: intialMap
// PreCondition: The boolean initialStart should be true.
// PostCondition: Creates a ROWS x COLS-sized 2D array grid of character "$".
//---------------------------------------------
void intialMap(char grid[ROWS][COLS]);

//---------------------------------------------
// Name: placeBalloon
// PreCondition: The boolean initialStart should be true.
// PostCondition: Places a balloon in a random location on the map.
//---------------------------------------------
void placeBalloon(char grid[ROWS][COLS], int balloonPosArr[]);

//---------------------------------------------
// Name: moveBalloon
// PreCondition: The boolean guessInputLoop should be true.
//               Player's guessed x position should be greater than or equal to 0
//               and less than or equal to constant ACTUAL_ROWS, or
//               player's guessed y position should be greater than or equal to 0
//               and less than or equal to constant ACTUAL_COLS.
// PostCondition: Randomly moves a balloon's position to one position up, down, left, or right.
//---------------------------------------------
void moveBalloon(char grid[ROWS][COLS], int balloonPosArr[]);

//---------------------------------------------
// Name: printMap
// PreCondition: The player should enter "1" on the main menu.
// PostCondition: Prints a map of the current status.
//---------------------------------------------
void printMap(char grid[ROWS][COLS]);

//---------------------------------------------
// Name: getGuess
// PreCondition: The player should enter "2" on the main menu.
// PostCondition: Stores the player's guessed position and places "G" on the corresponding position on the map.
//---------------------------------------------
void getGuess(char grid[ROWS][COLS], int guessPosArr[]);

//---------------------------------------------
// Name: checkGuess
// PreCondition: The player should enter "2" on the main menu.
//               The boolean guessInputLoop should be true.
//               Player's guessed x position should be greater than or equal to 0
//               and less than or equal to constant ACTUAL_ROWS, or
//               player's guessed y position should be greater than or equal to 0
//               and less than or equal to constant ACTUAL_COLS.
// PostCondition: Returns if the player's guessed position is equal to the current balloon's position.
//                If successfully guessed, print the total number of guesses and end the game.
//                If not, indicate which direction the balloon is.
//---------------------------------------------
bool checkGuess(int guessX, int guessY, int balloonX, int balloonY, int totalGuessTracker[]);

int main() {
    char grid[ROWS][COLS]; // Map
    int menu = 0; // Main menu input
    int balloonPosArr[2]; // Balloon's x = array[0] and y = array[1] position
    int guessPosArr[2]; // Player's guessed x = array[0] and y = array[1] position
    int totalGuessTracker[] = {0}; // Number of total guesses
    
    string restartString; // Required input to restart

    bool initialStart = true; // Is the game freshly started?
    bool isFound = false; // Does the player find the balloon?
    bool guessInputLoop = true; // Does the player enter valid input between 0 and the number of rows and columns?
    bool restartInputLoop = true; // Does the player enter valid input, y or n?
    
    cout << "Welcome to the Surveillance Balloon Tracker" << endl;
    cout << "You are searching for the surveillance balloon" << endl;
    
    do{
        
        // Initial setup of the map and the balloon
        if (initialStart) {
            intialMap(grid);
            placeBalloon(grid, balloonPosArr);
        }
        
        // Initial setup of booleans in case of the game restarted
        initialStart = false;
        guessInputLoop = true;
        restartInputLoop = true;

        // Main menu
        cout << "What would you like to do?" << endl;
        cout << "1. Display Map" << endl;
        cout << "2. Guess Location of Balloon" << endl;
        cout << "3. Exit" << endl;
        cin >> menu;
        
        switch (menu) {
            
            case 1:
                
                // Prints the map
                printMap(grid);
                break;
                
            case 2:
                
                while (guessInputLoop) {
                    
                    // Stores the player's guessed x and y position
                    getGuess(grid, guessPosArr);
                    
                    // Checks the player's input is valid
                    if (guessPosArr[0] < 0 || guessPosArr[0] > ACTUAL_ROWS || guessPosArr[1] < 0 || guessPosArr[1] > ACTUAL_COLS) {
                        guessInputLoop = true;
                        
                    } else {
                        
                        // Moves the balloon's position for one time
                        moveBalloon(grid, balloonPosArr);
                        totalGuessTracker[0]++;
                        
                        // Checks if the player's guessed position equals the balloon's position
                        if (!checkGuess(guessPosArr[0], guessPosArr[1], balloonPosArr[0], balloonPosArr[1], totalGuessTracker)) {
                            cout << "The balloon moves in the wind" << endl;
                            guessInputLoop = false;
                            isFound = false;
                
                        } else {
                            
                            // Asks if the player wants to replay the game
                            while (restartInputLoop) {
                                cout << "Would you like to play again? (y or n)" << endl;
                                cin >> restartString;
                                
                                if (restartString == "y") {
                                    initialStart = true;
                                    totalGuessTracker[0] = 0;
                                    restartInputLoop = false;
                                    guessInputLoop = false;
                                    isFound = false;
                                    
                                } else if (restartString == "n") {
                                    cout << "Thank you for Using the Surveillance Balloon Tracker" << endl;
                                    restartInputLoop = false;
                                    guessInputLoop = false;
                                    isFound = true;
                                    
                                } else {
                                    cout << "Invalid input - Please choose (y or n)" << endl;
                                }
                            }
                        }
                    }
                }
                break;
                
            case 3:
                
                // Exit
                cout << "Thank you for Using the Surveillance Balloon Tracker" << endl;
                isFound = true;
                break;
                
            default:
                
                // Asks the player to input again when didn't enter 1, 2, or 3
                cout << "Invalid input - Please choose again" << endl;
                break;
        }
    }
    while (!isFound);
}

void intialMap(char grid[ROWS][COLS]){
    
    // Creates a 2D array, ROWS x COLS
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = '$';
        }
    }
}

void placeBalloon(char grid[ROWS][COLS], int balloonPosArr[]) {
    
    // Assigns a random position for the balloon
    srand((unsigned int) time(NULL));
    int balloonX = rand() % ACTUAL_ROWS;
    int balloonY = rand() % ACTUAL_COLS;
    
    balloonPosArr[0] = balloonX;
    balloonPosArr[1] = balloonY;

    grid[balloonPosArr[0]][balloonPosArr[1]] = '$';
}

void moveBalloon(char grid[ROWS][COLS], int balloonPosArr[]) {
    
    // Assigns random movement of the balloon
    srand((unsigned int) time(NULL));
    
    // Random number generates from 1 to 4
    int moveBalloonPos = rand() % 3 + 1;
    
    switch(moveBalloonPos){
        
        case 1:
            
            // Balloon moves down
            balloonPosArr[1] = balloonPosArr[1] + 1;
            
            if (balloonPosArr[1] > ACTUAL_COLS){
                balloonPosArr[1] = balloonPosArr[1] - 1;
                break;
                
            } else {
                break;
            }
            
        case 2:
            
            
            // Balloon moves up
            balloonPosArr[1] = balloonPosArr[1] - 1;
            
            if (balloonPosArr[1] < 0){
                balloonPosArr[1] = balloonPosArr[1] + 1;
                break;
                
            } else {
                break;
            }
        
        case 3:
            
            // Balloon moves right
            balloonPosArr[0] = balloonPosArr[0] + 1;
            
            if (balloonPosArr[0] > ACTUAL_ROWS){
                balloonPosArr[0] = balloonPosArr[0] - 1;
                break;
                
            } else {
                break;
            }
            
        case 4:
            
            // Balloon moves left
            balloonPosArr[0] = balloonPosArr[0] - 1;
            
            if (balloonPosArr[0] < 0){
                balloonPosArr[0] = balloonPosArr[0] + 1;
                break;
                
            } else {
                break;
            }
    }
}

void printMap(char grid[ROWS][COLS]){
    
    // Numbering and spacing x-axis
    for (int i = 0; i < COLS; i++) {
        if (i <= 9 and i > 0) {
            cout << "  " << i;
            
        } else if (i > 9) {
            cout << " " << i;
            
        } else {
            cout << "     " << i;
        }
    }
    
    cout << endl;
    
    // Numbering and spacing y-axis
    for (int i = 0; i < ROWS; i++) {
        if (i <= 9) {
            cout << "  " << i;
        } else {
            cout << " " << i;
        }
        
        for (int j = 0; j < COLS; j++) {
            cout << "  " << grid[i][j];
        }
        cout << endl;
    }
}


void getGuess(char grid[ROWS][COLS], int guessPosArr[]){
    
    int guessX; // The player's guessed x position
    int guessY; // The player's guessed y position
    
    cout << "Enter the X coordinate (0 - " << ACTUAL_ROWS << "): " << endl;
    cin >> guessX;
    
    // Stores the player's guessed x position
    guessPosArr[0] = guessX;
    
    cout << "Enter the Y coordinate (0 - " << ACTUAL_COLS << "): " << endl;
    cin >> guessY;
    
    // Stores the player's guessed y position
    guessPosArr[1] = guessY;
    
    // Indicates the player's guessed position on the map
    grid[guessPosArr[0]][guessPosArr[1]] = 'G';
}


bool checkGuess(int guessX, int guessY, int balloonX, int balloonY, int totalGuessTracker[]){
    
    // Checks if the balloon's position equals the player's guessed position
    if (guessX == balloonX and guessY == balloonY) {
        cout << "Found balloon!" << endl;
        cout << "It took you " << totalGuessTracker[0] << " guesses to find the balloon"<< endl;
        return true;
        
    } else {
        cout << "You didn't find the balloon" << endl;
        
        if (guessX < balloonX) {
            cout << "Balloon is south of your guess" << endl;
            
        } else if (guessX > balloonX) {
            cout << "Balloon is north of your guess" << endl;
            
        } else {
            
            if (guessY < balloonY) {
                cout << "Balloon is east of your guess" << endl;;
                
            } else if (guessY > balloonY) {
                cout << "Balloon is west of your guess" << endl;;
            }
            
        }
        return false;
    }
}
