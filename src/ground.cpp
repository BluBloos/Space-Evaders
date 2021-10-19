#include "header/ground.h"

Ground::Ground() {
    this->collisionLayer = 0;
    this->horSpeed = 0;
    this->verSpeed = 0;
    this->width = 100;
    this->height = 100;
    this->currentVelocity = Vector2Zero();
    this->movable = false;
    this->mass = 1;
}

Ground::Ground(Vector2 v, int layer, float hor, float vert) : RenderableEntity(v, layer){
    this->collisionLayer = layer;
    this->horSpeed = hor;
    this->verSpeed = vert;
}

// what is going on with this initializer list?
Ground::Ground(Vector2 v, int layer, int width, int height) : RenderableEntity(v, layer) {
    this->collisionLayer = layer;
    this->width = width;
    this->height = height;
}

void Ground::ApplyForce(Vector2 force, float deltaTime ) {
    Vector2 accelVec = Vector2Scale(force, 1.0f / this->mass * deltaTime); 
    this->currentVelocity = Vector2Add(this->currentVelocity, accelVec);
}

void Ground::update(Game *game){

    float deltaTime = game->GetLastFrameTime();

    // Apply large amounts of air friction for "locking"
    /*{
        float currentVelLen = Vector2Length(this->currentVelocity);
        float accelFactor = -(Ground::airFriction / this->mass) * currentVelLen * currentVelLen;
        Vector2 accelVec = Vector2Scale( Vector2Negate(this->currentVelocity) , (accelFactor / currentVelLen * deltaTime) ); 
        this->currentVelocity = Vector2Add(this->currentVelocity, accelVec);
        if ( Vector2Length(this->currentVelocity) < powf(10, -10) ) {
            this->currentVelocity = Vector2Zero(); // snap the velocity to zero once we get below some super small threshold.
        } 
    }*/

    // Move according to velocity
    this->pos = Vector2Add(this->pos, this->currentVelocity); 

    // TODO: Add proper sizing to the ground. Becomes important once the player can move off the screen.
    DrawRectangleRec(Rectangle{this->pos.x, this->pos.y, (float)this->width, (float)this->height}, RED);
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
