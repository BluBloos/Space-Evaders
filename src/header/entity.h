#ifndef ENTITY_H
#define ENTITY_H

#include "raylib_wrapped.h"
class Game;

class Entity {
    public:
        Entity();

        // Build entity with position and collision layer 
        Entity(Vector2, int);

        Vector2 GetPos();
        void SetPos(Vector2);
        int GetLayer();

        // Update is a function that should be called every frame for all entities.
        // Entities are passed the main game object.
        virtual void update(Game *);

    protected: 
        Vector2 pos;
        static const int gravity = 400; // NOTE(Noah): Should use this type of initialization over gravity{400}
        int collisionLayer;
};

class RenderableEntity : public Entity {
    public:
        RenderableEntity();
        RenderableEntity(Vector2, int);
    
    public:
        virtual void update(Game *);
};
#endif