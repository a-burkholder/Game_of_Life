
#include<cmath>
#include<iostream>
#include<stdlib.h> 
#include<time.h>   
#include<random>
#include<thread>

#include "raylib.h"

using namespace std;

bool* initialize(const unsigned short& width, const unsigned short& height);
void randomize(bool matrix[], const unsigned short& width, const unsigned short& height);
void updateTurn(bool matrix[], const unsigned short& width, const unsigned short& height);
void printArray(bool matrix[], const unsigned short& width, const unsigned short& height);
void printArray(int matrix[], const unsigned short& width, const unsigned short& height);

int main2() {
    // Enter parameters section and initializations
    printf("Enter 'c' to continue: ");
    char input = ' ';
    do
        cin >> input;
    while (input != 'c'); // only move on if c is entered

    printf("Enter the matrix width: ");
    unsigned short width = 0;
    cin >> width;
    unsigned short height = width;

    printf("Initializing matrix\n");
    bool* game = initialize(width, height);

    printf("Randomizing\n");
    randomize(game, width, height);

    printf("Enter number of iterations: ");
    unsigned short iter = 0;
    cin >> iter;

    // START GAME HERE
    printf("Start--------------------------\n\n");
    printArray(game, width, height);
    for (int i = 1; i <= iter; i++) {
        updateTurn(game, width, height);
        printf("Turn %i--------------------------\n\n", i);
        this_thread::sleep_for(1000ms);
        printArray(game, width, height);
    }
    printf("End--------------------------\n\n");

    return 0;
}

// initialize() generates a new array of size width * height and populates it with 0s
// initialized as a 1D array, but is functionally a 2D array to make bass by reference easier for me
// returns the pointer to the generated array of size width * height
bool* initialize(const unsigned short& width, const unsigned short& height) {
    bool* game = new bool[width * height]; // Allocate new array for the game
    for (unsigned short y = height; y > 0; y--) { // fill with 0s
        for (unsigned short x = 0; x < width; x++) {
            game[(y - 1) * width + x] = 0;
        }
    }
    return game;
}

// randomize() randomizes the values of matrix
// input follows format: matrix[width * height]
void randomize(bool matrix[], const unsigned short& width, const unsigned short& height) {
    default_random_engine generator(time(NULL));
    discrete_distribution<int> distribution{ 6, 4 }; // gives 0 a 40% chance and 1 a 60% chance - ICKY data type (int) bc it can't do bools
    for (unsigned short y = height; y > 0; y--) { // fill with random 1s and 0s
        for (unsigned short x = 0; x < width; x++) {
            matrix[(y - 1) * width + x] = distribution(generator); // sets element to the random number
        }
    }
    return;
}

// updateTurn() takes a matrix of booleans and updates each position according to the rules of the game of life.
// Each position is updated according to the values at the time of entering, as to not have new values affect furthur updates to the next position.
// input follows format: matrix[width * height]
void updateTurn(bool matrix[], const unsigned short& width, const unsigned short& height) {
    static bool* updated = new bool[width * height]; // Allocate new array for the updated game
    for (unsigned short element = 0; element < width * height; element++) { // fill with 0s
        updated[element] = 0;
    }

    /*--update updated[] based on matrix[]--*/
    for (unsigned short y = height - 1; y > 1; y--) { // iterate through the elements, exclude borders because they are volcanoes (for simplicity)
        for (unsigned short x = 1; x < width - 1; x++) {
            static short yTarget;                   // targets so i can math a bit easier
            static short xTarget;
            yTarget = y - 1;
            xTarget = x;
            uint16_t coords = yTarget * width + xTarget;

            /*-count number of alive bits in 3x3 area around target-*/
            static short numAlive;
            numAlive = 0;
            for (int j = yTarget + 1; j >= yTarget - 1; j--) {
                for (int i = xTarget - 1; i <= xTarget + 1; i++) {
                    if (matrix[j * width + i] == 1) { numAlive++; }
                }
            }
            numAlive = numAlive - (uint8_t)matrix[yTarget * width + xTarget]; // subtract the target

            /*-actually do the update-*/
            if (matrix[coords] == 0 && numAlive == 3) { // if dead and can populate, do it
                updated[coords] = 1;
            }
            else { // if not dead, big switch
                switch (numAlive) {
                case 2:
                    updated[coords] = matrix[coords]; // sustained
                    break;
                case 3:
                    updated[coords] = matrix[coords]; // sustained
                    break;
                default:
                    updated[coords] = 0; // death by solitude, crowding, or bad coding (errors)
                }
            }
        }
    }

    /*--update matrix[] based on the now updated updated[]--*/
    for (unsigned short element = 0; element < width * height; element++) { // fill with 0s
        matrix[element] = updated[element];
    }

    return;
}

// printArray() prints a 2d array formated as a 1d array
// input follows format: matrix[width * height]
void printArray(bool matrix[], const unsigned short& width, const unsigned short& height) {
    for (unsigned short y = height; y > 0; y--) {
        for (unsigned short x = 0; x < width; x++) {
            cout << matrix[(y - 1) * width + x] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    return;
}

// testing version with ints to differentiate elements easier
// input follows format: matrix[width * height]
void printArray(int matrix[], const unsigned short& width, const unsigned short& height) {
    for (unsigned short y = height; y > 0; y--) {
        for (unsigned short x = 0; x < width; x++) {
            printf("%02u  ", matrix[(y - 1) * width + x]);
        }
        cout << endl;
    }
    cout << endl;
    return;
}
