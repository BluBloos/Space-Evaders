#include <raylib_wrapped.h>
#include <entity.h>
#include "iostream"

Vector2 Entity::GetPos() {
    return this->pos;
}

Entity::Entity() {
    this->pos = Vector2({0.0f,0.0f});
}

void Entity::Update() {
    // Does nothing, for now...
}

// NOTE(Noah): This code is going to be changed. Just wanted to write something
// down for testing purposes.
void RenderableEntity::Update() {
    DrawCircleV(Vector2({100.0f, 100.0f}), 100.0f, Color({190, 33, 55, 255}));
}