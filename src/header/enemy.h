#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public RenderableEntity{
    public:
        // Constructor
        // Building a enemy object takes in the position of the enemy object as well as the collision layer.
        Enemy(Vector2, int);
        void update(Game *) override;
        // Returns true if the player has touched enemy, otherwise will returns false.
        bool EnemyCollide(Entity*);
};

#endif
