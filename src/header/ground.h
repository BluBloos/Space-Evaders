#ifndef GROUND_H
#define GROUND_H

#include "entity.h"

class Ground : public RenderableEntity{
    public:
        // Constructor
        // Building a ground object takes in the position of the ground object as well as the collision layer.
        Ground(Vector2, int);
        void update(Game *) override;
        // TouchGround returns true if the target entity is touching this ground entity, otherwise TouchGround returns false.
        bool TouchGround(Entity*, float);
};

#endif
