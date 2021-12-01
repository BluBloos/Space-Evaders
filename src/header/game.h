#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include "star.h"
#include "particles.h"
#include <vector>
#include "oxygenTank.h"
#include "coin.h"

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
        Texture2D moonTexture;
        Texture2D enemyTexture;
        // void showTitle(Texture2D sprite);
        void showTitle();

        bool getGameOver();
        void switchGameOver();
        void showGameOver();

        // just debug things hehe
        Bullets *debugBulletObject;
        void tankRefill();
        int getO2();
        int timeCount;
        const int maxO2 = 100;

    private:
        std::vector<Entity *> characters;
        std::vector<Entity *> grounds;
        std::vector<tank> tanks;
        std::vector<coin> coins;
        Star stars[200];
        bool gameOver;
        bool settingsFlag;
        bool controlFlag;
        Camera2D camera;
        void updateCameraSmoothFollowInsideMap(float);
        int oxygenRemaining;
        int score;
};

#endif
