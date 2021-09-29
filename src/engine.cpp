// wrapped to avoid double inclusion.
#include "raylib_wrapped.h"

// Directly include the game code. Single file compilation model.
#include "game.cpp"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    // Make a new game object.
    // Thus calling the game initialization code.
    Game *myGame = new Game();
    
    InitWindow(screenWidth, screenHeight, "Space Evaders");
    SetTargetFPS(60);
    
    // Main engine loop
    // WindowShouldClose detects window close button or ESC key, things like this.
    while (!WindowShouldClose())
    {
        myGame->GameUpdateAndRender();
    }
    
    // Close window and OpenGL context
    CloseWindow();

    // Call the game de-init code. Done by deleting the game object.
    delete myGame;
    
    return 0;
}