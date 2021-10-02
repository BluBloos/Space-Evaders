#ifndef ENTITY_H
#define ENTITY_H
#include <raylib_wrapped.h>
class Entity {
    private: 
        Vector2 pos;
    public:
        Entity();
        Entity(Vector2);
        // This function will be called for all entities in the game, every frame.
        // There is no guarentee for the order in which the entities are updated.
        virtual void Update();
        Vector2 GetPos();
};

class RenderableEntity : public Entity {
    public:
        void Update();
};
#endif