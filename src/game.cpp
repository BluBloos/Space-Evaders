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
    characters.push_back(new Player(Vector2{500.0f, 100.0f}, 0));
    grounds.push_back(new Ground(Vector2{0.0f, 400.0f}, 0, 0, 0));
}

// Define what will happen each frame of the game.
void Game::GameUpdateAndRender() {
    BeginDrawing(); 
    ClearBackground(RAYWHITE);

    // Go through loop of all entities and call update.
    for (Entity *entity : characters) {
        entity->update();
    }    
    for (Entity *entity : grounds) {
        entity->update();
    }

    EndDrawing();
}

// Define the things that will happen when the game is closed.
Game::~Game() {

    // Clean up entities.
    for (unsigned int i = 0; i < characters.size(); i++) {
        Entity *entity = characters[i];
        delete entity; // NOTE(Noah): Pretty sure this works...
    }
    for (unsigned int i = 0; i < grounds.size(); i++) {
        Entity *entity = grounds[i];
        delete entity;
    }

    std::cout << "Game has been closed\n";
}
