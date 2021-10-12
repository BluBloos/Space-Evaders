// wrapped to avoid double inclusion.
// Directly include the game code. Single file compilation model.
#include "game.cpp"
#include "header/raylib_wrapped.h"

// Jenkins code.
int main(void)
{
    const int screenWidth = 885;
    const int screenHeight = 500;
    
    // Make a new game object.
    // // Thus calling the game initialization code.
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