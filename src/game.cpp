#include "raylib_wrapped.h" // wrapped to avoid double inclusion.
#include "iostream"
#include <game.h>

// Define the things that happen when the game is initialized.
Game::Game() {
    std::cout << "Game has been initialized" << std::endl;
}

// Define what will happen each frame of the game.
void Game::GameUpdateAndRender() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, World!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
}

// Define the things that will happen when the game is closed.
Game::~Game() {
    std::cout << "Game has been closed" << std::endl;
}
