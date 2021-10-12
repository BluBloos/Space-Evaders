#include "header/entity.h"

// Constructors
Entity::Entity() {
    this->pos = Vector2({0.0f,0.0f});
}
Entity::Entity(Vector2 p, int layer){
    this->pos = p;
    this->collisionLayer = layer;
}
// Destructor
Entity::~Entity(){
    delete this;
}
// Set, get
Vector2 Entity::GetPos() {
    return this->pos;
}
void Entity::SetPos(Vector2 p){
    this->pos = p;
}
int Entity::GetLayer(){
    return this->collisionLayer;
}
// public functions
void Entity::update(){}


// Constructors
RenderableEntity::RenderableEntity(){}
RenderableEntity::RenderableEntity(Vector2 v, int layer):Entity(v, layer){}
// public functions
void RenderableEntity::update(){}
