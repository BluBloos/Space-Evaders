#include <iostream>
#include <vector>
#include "player.cpp"
#include "entity.cpp"
#include "ground.cpp"
#include "header/gameover.h"

gameover::gameover(Player player) { // creates a rectangle over the screen with text
    BeginDrawing();
    DrawRectangle(GetScreenWidth()*0.1, GetScreenHeight()*0.1, GetScreenWidth()*0.8, GetScreenHeight()*0.8, GRAY);
    DrawText("Game Over", GetScreenWidth()*0.4, GetScreenHeight()*0.45, 50, RAYWHITE);
    DrawText("Press Enter to Respawn", GetScreenWidth()*0.225, GetScreenHeight()*0.55, 50, RAYWHITE);
    EndDrawing();

    player.alive = false; //locks player movement
    while(player.alive == false){
        if(IsKeyDown(KEY_ENTER)){ // loop until enter is pressed
            player.alive = true;
            // TODO: respawn the player back at the start of the level
            // this->pos.x = STARTX
            // this->pos.y = STARTY
        }

}


