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
<<<<<<< HEAD
    this->characters.push_back(new Player((Vector2){500.0f, 0.0f}, 0));
    this->grounds.push_back(new Ground((Vector2){-20.0f, 200.0f}, 0));
=======
    this->characters.push_back(new Player((Vector2){500.0f, 100.0f}, 0));
    this->grounds.push_back(new Ground((Vector2){-20.0f, 400.0f}, 0, 1000, 200));
    // Add a moveable platform for player to jump onto!
    Ground *epic_ground = new Ground((Vector2){400.0f, 200.0f}, 0, 200, 100);
    epic_ground->SetMovable(true, 0, -1, 100, 100);
    //epic_ground->SetOscillation(); // set the platform to go back and forth in movement
    this->grounds.push_back((Entity *)epic_ground);
>>>>>>> 9d2b4ef4a73eeed5e1dae301d270585ea7d7106c
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
    for (unsigned int i = 0; i < this->grounds.size(); i++) {
        Entity *entity = this->grounds[i];
        entity->update(this);
    }
    for (unsigned int i = 0; i < this->characters.size(); i++) {
        Entity *entity = this->characters[i];
        entity->update(this);
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
