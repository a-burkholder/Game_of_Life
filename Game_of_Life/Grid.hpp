#pragma once
#include<vector>
#include<array>

class Grid {
public:
	Grid(int width, int height, int tileSizeIn) 
	: rows(height / tileSizeIn), columns(width / tileSizeIn), tileSize(tileSizeIn), matrixv(rows, std::vector<int>(columns, 0)) {
		matrix = new int[rows * columns];
	};
	void Drawv();
	void SetTile(int row, int column, int value);
		
private:
	int rows;
	int columns;
	int tileSize;
	std::vector<std::vector<int>> matrixv;
	int* matrix;

};