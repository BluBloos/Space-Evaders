#include "header/enemy.h"
#include "character.cpp"

Enemy::Enemy() : Character () {
    this->collisionLayer = 0;
    this->oscillationX = 0;
    this->oscillationY = 0;
    this->dirx = dirx;
    this->diry = diry; 
    this->width = 50;
    this->height = 50;
    this->currentVelocity = Vector2Zero();
    this->movable = false;
    this->mass = 1;
}

Enemy::Enemy(Vector2 v, int layer) : Character (v, layer) {
    this->collisionLayer = layer;
}

void Enemy::update(Game *game){

    float deltaTime = game->GetLastFrameTime();

    // Apply large amounts of air friction for "locking"
    {
        float currentVelLen = Vector2Length(this->currentVelocity);
        if (currentVelLen != 0) {
            float accelFactor = (Enemy::airFriction / this->mass) * currentVelLen;
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

	DrawCircle(this->pos.x, this->pos.y, 25.0f, RED);
}

void Enemy::ApplyForce(Vector2 force, float deltaTime ) {
    Vector2 accelVec = Vector2Scale(force, 1.0f / this->mass * deltaTime); 
    this->currentVelocity = Vector2Add(this->currentVelocity, accelVec);
}

void Enemy::SetMovable(bool isMovable, float dirx, float diry, float osx, float osy)
{
    this->movable = isMovable;
    this->dirx = dirx;
    this->diry = diry;
    this->oscillationX = osx;
    this->oscillationY = osy;
};

bool Enemy::EnemyCollide(Entity *target){
    // TODO: Change collision code to raylib function involving two hitboxes
    Player *player = (Player *)target;
    return (this->collisionLayer == player->GetLayer()) &&
			sqrt(pow(this->pos.x - (player->GetPos().x + 10), 2) + pow(this->pos.y - (player->GetPos().y - 26), 2) * 1.0) <= 25;
}
