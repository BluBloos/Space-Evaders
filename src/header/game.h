#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include <vector>

class Game {
    
    public:
        Game(); // Constructor
        ~Game(); // Destructor
    
        // Function for game to implement and is to be called for each frame
        // to be rendered.    
        void GameUpdateAndRender();

        std::vector<Entity *> GetGrounds(); // Will return all the ground entities
        std::vector<Entity *> GetCharacters(); // Will return all the ground entities
        float GetLastFrameTime();
        void showSettings();
        void setSettingsFlag();
        void setControlFlag();
        bool getControlFlag();

        bool onTitle;
        Texture2D titleSprite;
        // void showTitle(Texture2D sprite);
        void showTitle();

        bool getGameOver();
        void switchGameOver();
        void showGameOver();

    private:
        std::vector<Entity *> characters;
        std::vector<Entity *> grounds;
        bool gameOver;
        bool settingsFlag;
        bool controlFlag;
        Camera2D camera;
        void updateCameraSmoothFollowInsideMap(float);
};

#endif



