#ifndef GROUND_H
#define GROUND_H

#include "entity.h"

class Ground : public RenderableEntity{
    public:
        // Constructor
        Ground(Vector2, int);
    public:
        // func
        void update() override;
        bool TouchGround(Player*, float);
};

#endif
