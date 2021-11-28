#include <iostream>
#include <vector>
#include "player.cpp"
#include "entity.cpp"
#include "ground.cpp"
#include "header/game.h"


// Define the things that happen when the game is initialized.
Game::Game() {
    std::cout << "Game has been initialized\n\n";
    // Create game entities.
    this->characters.push_back(new Player((Vector2){500.0f, 100.0f}, 0));
    this->grounds.push_back(new Ground((Vector2){-20.0f, 400.0f}, 0, 1000, 200));
    // Add a moveable platform for player to jump onto!
    Ground *epic_ground = new Ground((Vector2){400.0f, 200.0f}, 0, 200, 100);
    epic_ground->SetMovable(true, 0, -1, 100, 100);
    //epic_ground->SetOscillation(); // set the platform to go back and forth in movement
    this->grounds.push_back((Entity *)epic_ground);

    this->controlFlag = true; // control flag to swap between WASD and arrow keys
    this->settingsFlag = false; // settings flag to display settings
}

std::vector<Entity *> Game::GetGrounds() {
    return this->grounds;
}

float Game::GetLastFrameTime() {
    return GetFrameTime();
}

// Define what will happen each frame of the game.
void Game::GameUpdateAndRender() {
    BeginDrawing(); 
    ClearBackground(RAYWHITE);

    // Calling raylib function GetFrameTime to return the time in seconds for the last frame drawn.
    float deltaTime = GetFrameTime();

    if (IsKeyPressed(KEY_P)) { // if user hits escape
        this->setSettingsFlag(); // switch settings flag
    }

    if (settingsFlag){
        showSettings();
    }

    else {
        // Go through loop of all entities and call update.
        for (unsigned int i = 0; i < this->grounds.size(); i++) {
            Entity *entity = this->grounds[i];
            entity->update(this);
        }
        for (unsigned int i = 0; i < this->characters.size(); i++) {
            Entity *entity = this->characters[i];
            entity->update(this);
        }
    }


    EndDrawing();
}

// Define the things that will happen when the game is closed.
Game::~Game() {

    // Clean up entities.
	for (unsigned int i = 0; i < this->grounds.size(); i++) {
	        Entity *entity = this->grounds[i];
	        delete entity;
	}
    for (unsigned int i = 0; i < this->characters.size(); i++) {
        Entity *entity = this->characters[i];
        delete entity; // NOTE(Noah): Pretty sure this works...
    }


    std::cout << "Game has been closed\n";
}

void Game::showSettings() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawText("Controls", GetScreenWidth()*0.325, GetScreenHeight()*0.1, 75, RAYWHITE);
    DrawText("Press Enter to Switch Movement", GetScreenWidth()*0.1, GetScreenHeight()*0.4, 40, RAYWHITE);

    if (IsKeyPressed(KEY_ENTER)){ setControlFlag(); }

    if (getControlFlag()) {
        DrawText("Movement: WASD", GetScreenWidth()*0.1, GetScreenHeight()*0.5, 40, RAYWHITE);
    }

    else {
        DrawText("Movement: Arrow Keys", GetScreenWidth()*0.1, GetScreenHeight()*0.5, 40, RAYWHITE);
    }

    DrawText("Jump: Space", GetScreenWidth()*0.1, GetScreenHeight()*0.6, 40, RAYWHITE);
    DrawText("Gravity Flip: F", GetScreenWidth()*0.1, GetScreenHeight()*0.7, 40, RAYWHITE);
    DrawText("Black Hole: G", GetScreenWidth()*0.1, GetScreenHeight()*0.8, 40, RAYWHITE);
}

void Game::setSettingsFlag() {
    this->settingsFlag = !this->settingsFlag; // switch flag
}

void Game::setControlFlag() {
    this->controlFlag = !this->controlFlag; // switch control flag
}

bool Game::getControlFlag() { return this->controlFlag; }