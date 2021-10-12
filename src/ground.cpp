#include "header/ground.h"

Ground::Ground(Vector2 v, int layer) : RenderableEntity(v, layer){
    this->collisionLayer = layer;
}

void Ground::update(){
    DrawRectangleRec(Rectangle{this->pos.x, this->pos.y, 1000.0f, 200.0f}, GRAY);
}

bool Ground::TouchGround(Player *target, float delta){
    return (this->collisionLayer  == target->GetLayer()) &&
            this->pos.x           <= target->GetPos().x &&
            this->pos.x + 1000.0f >= target->GetPos().x &&
            this->pos.y           >= target->GetPos().y &&
            this->pos.y            < target->GetPos().y + target->GetCurVerSpeed()*delta;
}