#include "header/ground.h"

Ground::Ground(Vector2 v, int layer, float hor, float vert) : RenderableEntity(v, layer){
    this->collisionLayer = layer;
    this->horSpeed = hor;
    this->vertSpeed = vert;
}

void Ground::update(){
    DrawRectangleRec(Rectangle{this->pos.x += GetFrameTime()*this->horSpeed, this->pos.y += GetFrameTime()*this->vertSpeed, 1000.0f, 200.0f}, GRAY);
}

bool Ground::TouchGround(Player *target, float delta){
    return (this->collisionLayer  == target->GetLayer()) &&
            this->pos.x           <= target->GetPos().x &&
            this->pos.x + 1000.0f >= target->GetPos().x &&
            this->pos.y           >= target->GetPos().y &&
            this->pos.y            < target->GetPos().y + target->GetCurVerSpeed()*delta;
}
