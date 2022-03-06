// wrapped to avoid double inclusion.
// Directly include the game code. Single file compilation model.
#include "stdio.h"
#include "game.cpp"
#include "header/raylib_wrapped.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

Game *globalGame = NULL;

void UpdateDrawFrame(void) {
    if (globalGame != NULL) {
        globalGame->GameUpdateAndRender();
    }
}

int main(void)
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Space Evaders");

    // Make a new game object.
    // Note(Chong): The game must be initialized after InitWindow. Because OpenGL context is required for textures
    Game *myGame = new Game();
    globalGame = myGame;
    
    SetTargetFPS(60);

    // Main engine loop
    // WindowShouldClose detects window close button or ESC key, things like this.
#ifdef PLATFORM_WEB
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif
        
    // Call the game de-init code. Done by deleting the game object.
    delete myGame;

    // Close window and OpenGL context
    CloseWindow();
    
    return 0;
}