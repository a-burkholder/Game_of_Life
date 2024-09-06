#include "Grid.hpp"
#include<raylib.h>
#include<time.h>   
#include<random>

// Draw()
// -Draws every rectangle in the game
void Grid::Draw(){
	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {
			Color color = matrix[row][column] ? Color{ 0, 255, 0, 255 } : Color{ 55, 55, 55, 255 };
			DrawRectangle(column * tileSize, row * tileSize, tileSize - 1, tileSize - 1, color);
		}
	}
}

// SetTile(int row, int column, int value)
// -Sets a specific tile a specific value
// -Testing purposes
void Grid::SetTile(int row, int column, int value) {
	if (row >= 0 && row < rows && column >= 0 && column < columns) {
		matrix[row][column] = value;
	}
}

// Randomize()
// -Randomizes the whole game
void Grid::Randomize() {
	std::default_random_engine generator(time(NULL));
	std::discrete_distribution<int> distribution{ 6, 4 }; // gives 0 a 40% chance and 1 a 60% chance - ICKY data type (int) bc it can't do bools
	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {
			matrix[row][column] = distribution(generator); // sets element to the random number
		}
	}
	return;
}

// UpdateTurn()
// Updates the whole board based on the rules
void Grid::UpdateTurn() {
    static std::vector<std::vector<int>> updated = matrix; // Allocate new array for the updated game

    for (int row = 0; row < rows; row++) { // sets elements in updated to 0
        for (int column = 0; column < columns; column++) {
            updated[row][column] = 0;
        }
    }

    /*--update updated[] based on matrix[]--*/
    for (int row = 1; row < rows - 1; row++) {
        for (int column = 1; column < columns - 1; column++) {
            static short yTarget;                   // targets so i can math a bit easier
            static short xTarget;



            /*-count number of alive bits in 3x3 area around target-*/
            static int numAlive;
            numAlive = 0;
            for (int j = row - 1; j <= row + 1; j++) {
                for (int i = column - 1; i <= column + 1; i++) {
                    if (matrix[j][i] == 1) { numAlive++; }
                }
            }
            numAlive = numAlive - matrix[row][column]; // subtract the target

            /*-actually do the update-*/
            if (matrix[row][column] == 0 && numAlive == 3) { // if dead and can populate, do it
                updated[row][column] = 1;
            }
            else { // if not dead, big switch
                switch (numAlive) {
                case 2:
                    updated[row][column] = matrix[row][column]; // sustained
                    break;
                case 3:
                    updated[row][column] = matrix[row][column]; // sustained
                    break;
                default:
                    updated[row][column] = 0; // death by solitude, crowding, or bad coding (errors)
                }
            }
        }
    }


    matrix = updated;
}