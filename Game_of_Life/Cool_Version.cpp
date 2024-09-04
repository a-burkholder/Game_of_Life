#include<iostream>
#include<raylib.h>
#include "Grid.hpp"


int main() {
    int fps = 12; // max fps

    Color darkGrey = Color{ 17, 17, 17, 255 };
    Color lightGrey = Color{ 40, 40, 40, 255 };
    Color green = Color{ 17, 150, 17, 255 };

    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 1000;

    const int TILE_SIZE = 10;

   

    std::cout << "Hello World" << std::endl;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My first RAYLIB program!");
    SetTargetFPS(fps);
    Grid grid(WINDOW_WIDTH, WINDOW_HEIGHT, TILE_SIZE);
    grid.SetTile(0, 0, 1);
    grid.SetTile(2, 1, 1);
    grid.SetTile(3, 4, 1);

    while (WindowShouldClose() == false) {
        //events


        //state




        //drawing
        BeginDrawing();
        ClearBackground(darkGrey);

        grid.Drawv();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}