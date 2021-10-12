#pragma once

#include "entity.h"
#include <vector>

std::vector<Entity *> characters;
std::vector<Entity *> grounds;

class Game {
    
    public:
        Game(); // Constructor
        ~Game(); // Destructor
    
    public:
        // Function for game to implement and is to be called for each frame
        // to be rendered.    
        void GameUpdateAndRender();
};



