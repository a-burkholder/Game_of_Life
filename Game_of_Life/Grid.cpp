#include "Grid.hpp"
#include<raylib.h>

void Grid::Drawv(){
	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {
			Color color = matrixv[row][column] ? Color{ 0, 255, 0, 255 } : Color{ 55, 55, 55, 255 };
			DrawRectangle(column * tileSize, row * tileSize, tileSize - 1, tileSize - 1, color);
		}
	}
}

void Grid::SetTile(int row, int column, int value) {
	if (row >= 0 && row < rows && column >= 0 && column < columns) {
		matrixv[row][column] = value;
		matrix[row * rows + column] = value;
	}
}
