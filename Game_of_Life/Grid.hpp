#pragma once
#include<vector>
#include<time.h>   
#include<random>

class Grid {
public:
	Grid(int width, int height, int tileSizeIn) 
	: rows(height / tileSizeIn), columns(width / tileSizeIn), tileSize(tileSizeIn), matrix(rows, std::vector<int>(columns, 0)) {};
	void Draw();
	void SetTile(int row, int column, int value);
	void Randomize();
	void UpdateTurn();
		
private:
	int rows;
	int columns;
	int tileSize;
	std::vector<std::vector<int>> matrix;
	

};