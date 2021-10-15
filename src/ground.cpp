#include "header/ground.h"

Ground::Ground(Vector2 v, int layer, float hor, float vert) : RenderableEntity(v, layer){
    this->collisionLayer = layer;
    this->horSpeed = hor;
    this->vertSpeed = vert;
}

void Ground::update(Game *game){
    // TODO: Add proper sizing to the ground. Becomes important once the player can move off the screen.
    DrawRectangleRec(Rectangle{this->pos.x, this->pos.y, 1000.0f, 200.0f}, GRAY);
}

bool Ground::TouchGround(Entity *target, float deltaTime){
    // TODO: Once again, account for the fact that we want variable sized grounds.
    Player *player = (Player *)target;
    return (this->collisionLayer  == player->GetLayer()) &&
            this->pos.x           <= player->GetPos().x &&
            this->pos.x + 1000.0f >= player->GetPos().x &&
            this->pos.y           >= player->GetPos().y &&
            this->pos.y            < player->GetPos().y + player->GetCurrentVerticalSpeed() * deltaTime;
}
