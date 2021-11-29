// wrapped to avoid double inclusion.
// Directly include the game code. Single file compilation model.
#include "game.cpp"
#include "header/raylib_wrapped.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Space Evaders");

    // Make a new game object.
    Game *myGame = new Game(); // Note(Chong): The game must be initialized after InitWindow. Because OpenGL context is required for textures
    
    SetTargetFPS(60);

    // Main engine loop
    // WindowShouldClose detects window close button or ESC key, things like this.
    while (!WindowShouldClose())
    {
        myGame->GameUpdateAndRender();
    }
        
    // Call the game de-init code. Done by deleting the game object.
    delete myGame;

    // Close window and OpenGL context
    CloseWindow();
    
    return 0;
}