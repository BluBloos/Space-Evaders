#include "header/ground.h"

/*
Ground::Ground(Vector2 v, int layer, float hor, float vert, int dirx, int diry) : RenderableEntity(v, layer){
    this->collisionLayer = layer;
    this->oscillationX = hor;
    this->oscillationY = vert;
    this->dirx = dirx;
    this->diry = diry;
}
*/

Ground::Ground() {
    this->collisionLayer = 0;
    this->oscillationX = 0;
    this->oscillationY = 0;
    this->width = 100;
    this->height = 100;
    this->currentVelocity = Vector2Zero();
    this->movable = false;
    this->mass = 1;
    this->dirx = 0;
    this->diry = 0;
}

/*
Ground::Ground(Vector2 v, int layer) : RenderableEntity(v, layer){
    this->collisionLayer = layer;
}
*/

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

void Ground::SetMovable(bool isMovable, float dirx, float diry, float osx, float osy)
{
    this->movable = isMovable;
    this->dirx = dirx;
    this->diry = diry;
    this->oscillationX = osx;
    this->oscillationY = osy;
};

void Ground::update(Game *game){

    float deltaTime = game->GetLastFrameTime();

    // Apply large amounts of air friction for "locking"
    {
        float currentVelLen = Vector2Length(this->currentVelocity);
        if (currentVelLen != 0) {
            float accelFactor = (Ground::airFriction / this->mass) * currentVelLen;
            Vector2 accelVec = Vector2Scale( Vector2Negate(this->currentVelocity) , (accelFactor / currentVelLen * deltaTime) ); 
            this->currentVelocity = Vector2Add(this->currentVelocity, accelVec);
            if ( Vector2Length(this->currentVelocity) < powf(10, -10) ) {
                this->currentVelocity = Vector2Zero(); // snap the velocity to zero once we get below some super small threshold.
            } 
        }
    }

    // Move according to velocity
    this->pos = Vector2Add(this->pos, Vector2Scale(this->currentVelocity, deltaTime) ); 

    // Now move the platform according to the oscillation
    if (this->IsMovable())
    {    
        this->counter += 1;
        if (this->counter >= 120) {
            this->dirx = -(this->dirx);
            this->diry = -(this->diry);
            this->counter = 0;
        }
        // Modify the position
        {
            this->pos.x += deltaTime * this->oscillationX * this->dirx;
            this->pos.y += deltaTime * this->oscillationY * this->diry;
        }
    }

    DrawRectangleRec(Rectangle{this->pos.x, this->pos.y, (float)this->width, (float)this->height}, RED);
}

bool Ground::TouchGround(Player *target, float deltaTime){
    // TODO: Once again, account for the fact that we want variable sized grounds.
    Player *player = (Player *)target;
    return ( this->collisionLayer  == player->GetLayer() &&
            this->pos.x           <= player->GetPos().x &&
            this->pos.x + this->width >= player->GetPos().x &&
            this->pos.y           <= player->GetPos().y &&
            this->pos.y + this->height > player->GetPos().y );
}

float Ground::getWidth(){
    return this->width;
}
float Ground::getHeight(){
    return this->height;
}