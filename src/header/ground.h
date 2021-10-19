#ifndef GROUND_H
#define GROUND_H

#include "entity.h"

class Ground : public RenderableEntity{
    public:
        // Constructor
        // Building a ground object takes in the position of the ground object as well as the collision layer.
        // Also takes in the horizontal and vertical speed.
        Ground(Vector2, int, float, float);

        // This ground constructor takes in the position, collision layer, width and height.
        Ground(Vector2, int, int, int);

        void update(Game *) override;
        // TouchGround returns true if the target entity is touching this ground entity, otherwise TouchGround returns false.
        bool TouchGround(Entity*, float);
        void SetMoveable(bool isMovable) {this->movable = isMovable};
        bool IsMovable() (return this->movable);
    private:
        bool movable;
        float horSpeed;
        float verSpeed;
        int width;
        int height;
};

#endif
