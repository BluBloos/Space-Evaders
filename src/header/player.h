#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <vector>
 
class Player : public RenderableEntity{
    public:
        Player(Vector2, int);
    public:
        void update() override;
        float GetCurVerSpeed();
    private:
        // attr
        float curVerSpeed;
        const float horSpeed{350.0f};
        const float verSpeed{310.0f};
        bool canJump;
        bool touchGround;
        // func
        void run(float);
        void jump(float);
};

#endif