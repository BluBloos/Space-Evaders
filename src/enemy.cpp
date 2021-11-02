#include "header/enemy.h"

Enemy::Enemy(Vector2 v, int layer, float hor, float vert, int dirx, int diry) : RenderableEntity(v, layer){
    this->collisionLayer = layer;
    this->horSpeed = hor;
    this->verSpeed = vert;
    this->dirx = dirx;
    this->diry = diry; 
}

void Enemy::update(Game *game){
    // Draws the sprite of the enemy at its position
	DrawCircle(this->pos.x, this->pos.y, 50.0f, RED);
}

bool Enemy::EnemyCollide(Entity *target){
    // TODO: Currently the radius of player and enemies are 50 units; perhaps make it variable for later on
	// when sprite are used of change collision detection code
    Player *player = (Player *)target;
    return (this->collisionLayer == player->GetLayer()) &&
			sqrt(pow(this->pos.x - player->GetPos().x, 2) + pow(this->pos.y - player->GetPos().y, 2) * 1.0) <= 100;
}
