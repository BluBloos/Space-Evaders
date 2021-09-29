#include "raylib.h"
#include <iostream>

using namespace std;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    cout << "Hello, World!" << endl;
    
    InitWindow(screenWidth, screenHeight, "Space Evaders");
    SetTargetFPS(60);
    
    
    // Main engine loop
    // WindowShouldClose detects window close button or ESC key, things like this.
    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        DrawText("Hello, World!", 190, 200, 20, LIGHTGRAY);
        
        EndDrawing();
    }
    
    // Close window and OpenGL context
    CloseWindow();
    
    return 0;
}