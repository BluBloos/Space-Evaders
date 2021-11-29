#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "animator.h"

class Player : public RenderableEntity{
    public:
        // player constructor takes in the player position and render layer.
        Player(Vector2, int);

        void update(Game *) override;
        float GetCurrentVerticalSpeed();
<<<<<<< HEAD

=======
        constexpr static const float blackHoleCoeff = 20.0f;
        
>>>>>>> 9d2b4ef4a73eeed5e1dae301d270585ea7d7106c
    private:
        // attr
        float currentVerticalSpeed;
        const float horSpeed = 280.0f;
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
        
        void InitializeAnimations() override;
        void SetTransitions() override;
        void SetConditions() override;
};

#endif
