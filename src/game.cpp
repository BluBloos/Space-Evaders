#include <iostream>
#include <vector>
#include "player.cpp"
#include "entity.cpp"
#include "ground.cpp"
#include "header/game.h"
#include <iostream>


// Define the things that happen when the game is initialized.
Game::Game() {
    std::cout << "Game has been initialized\n\n";
    // Create game entities.
    this->characters.push_back(new Player((Vector2){500.0f, 0.0f}, 0));
    this->grounds.push_back(new Ground((Vector2){-20.0f, 200.0f}, 0));
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

    // Go through loop of all entities and call update.
    for (unsigned int i = 0; i < this->characters.size(); i++) {
        Entity *entity = this->characters[i];
        entity->update(this);
    }
    for (unsigned int i = 0; i < this->grounds.size(); i++) {
        Entity *entity = this->grounds[i];
        entity->update(this);
    }

    EndDrawing();
}

// Define the things that will happen when the game is closed.
Game::~Game() {

    // Clean up entities.
    for (unsigned int i = 0; i < this->characters.size(); i++) {
        Entity *entity = this->characters[i];
        delete entity; // NOTE(Noah): Pretty sure this works...
    }
    for (unsigned int i = 0; i < this->grounds.size(); i++) {
        Entity *entity = this->grounds[i];
        delete entity;
    }

    std::cout << "Game has been closed\n";
}
