#ifndef ENTITY_H
#define ENTITY_H

#include "raylib_wrapped.h"

class Entity {
    public:
        Entity();
        Entity(Vector2, int);
        ~Entity();
    
    public:
        Vector2 GetPos();
        void SetPos(Vector2);
        int GetLayer();

        virtual void update();

    protected: 
        Vector2 pos;
        static const int gravity{400};
        int collisionLayer;
};

class RenderableEntity : public Entity {
    public:
        RenderableEntity();
        RenderableEntity(Vector2, int);
    
    public:
        virtual void update();
};
#endif