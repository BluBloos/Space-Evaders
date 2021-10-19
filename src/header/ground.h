#ifndef GROUND_H
#define GROUND_H

#include "entity.h"

class Ground : public RenderableEntity{
    public:
        // Constructor
        // Building a ground object takes in the position of the ground object as well as the collision layer.
        Ground(Vector2, int);
        Ground(Vector2, int, float, float, int, int);
    public:
        // func
        void update();
        bool TouchGround(Player*, float);
    private:
        float horSpeed;
        float verSpeed;
        int dirx;
        int diry;
        int counter = 0;
        void update(Game *);
        // TouchGround returns true if the target entity is touching this ground entity, otherwise TouchGround returns false.
        bool TouchGround(Entity*, float);
};

#endif
