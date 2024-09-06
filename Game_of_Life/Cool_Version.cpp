#include<iostream>
#include<raylib.h>
#include<raymath.h>  
#include "Grid.hpp"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))


int main() {
    // Definitions
    int fps = 14; // max fps

    Color darkGrey = Color{ 17, 17, 17, 255 };
    Color lightGrey = Color{ 40, 40, 40, 255 };
    Color green = Color{ 17, 150, 17, 255 };

    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 1000;
    int gameWidth = 1000;
    int gameHeight = 1000;

    const int TILE_SIZE = 10;

    // Initializations
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game of Life");
    SetWindowMinSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    SetTargetFPS(fps);
    RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use
    Grid grid(WINDOW_WIDTH, WINDOW_HEIGHT, TILE_SIZE);
    grid.Randomize();

    // Game loop
    while (WindowShouldClose() == false) {
        // State updates
        grid.UpdateTurn();
        float scale = MIN((float)GetScreenWidth() / gameWidth, (float)GetScreenHeight() / gameHeight);

        // Event handling
        if (IsKeyPressed(KEY_R)) {
            grid.Randomize();
        }

        // Drawing
        BeginTextureMode(target);
        ClearBackground(darkGrey);  // Clear render texture background color
        grid.Draw();

        EndTextureMode();


        BeginDrawing();
        ClearBackground(darkGrey);
        DrawTexturePro(
            target.texture, 
            Rectangle { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height }, 
            Rectangle { (GetScreenWidth() - ((float)gameWidth * scale)) * 0.5f,
            (GetScreenHeight() - ((float)gameHeight * scale)) * 0.5f,
            (float)gameWidth* scale, (float)gameHeight* scale },
            Vector2 { 0, 0 }, 0.0f, WHITE);
        EndDrawing();

    }

    // Exit
    CloseWindow();
    return 0;
}