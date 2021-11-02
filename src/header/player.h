#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <vector>
 
class Player : public RenderableEntity{
    public:
        // player constructor takes in the player position and render layer.
        Player(Vector2, int);
        void update(Game *) override;
        float GetCurrentVerticalSpeed();
        constexpr static const float blackHoleCoeff = 20.0f;
        
    private:
        // attr
        float currentVerticalSpeed;
        const float horSpeed = 600.0f;
        const float verSpeed = 310.0f;
        bool inAir;
        int flipMultiplier;
        
        
        
        // The run function for the player updates the horizontal movement of the player based on frame deltaTime
        // and the direction of running.
        void run(float, float);

        // Calling the run function will make initiate a player jump sequence.
        void jump();

        // gravity flip function, triggered by pressing f
        void gravityFlip();
};

#endif
