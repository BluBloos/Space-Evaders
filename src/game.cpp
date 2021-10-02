#include "raylib_wrapped.h" // wrapped to avoid double inclusion.
#include "iostream"
#include <game.h>
#include <entity.cpp>

// Define the things that happen when the game is initialized.
Game::Game() {
    std::cout << "Game has been initialized" << std::endl;

    // Create game entities.
    this->entities.push_back(new RenderableEntity());
}

// Define what will happen each frame of the game.
void Game::GameUpdateAndRender() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, World!", 190, 200, 20, LIGHTGRAY);

    // Go through loop of all entities and call update.
    for (Entity *entity : this->entities) {
        
        entity->Update();
    }

    EndDrawing();
}

// Define the things that will happen when the game is closed.
Game::~Game() {

    // Clean up entities.
    for (unsigned int i = 0; i < this->entities.size(); i++) {
        Entity *entity = this->entities[i];
        delete entity; // NOTE(Noah): Pretty sure this works...
    }

    std::cout << "Game has been closed" << std::endl;
}
