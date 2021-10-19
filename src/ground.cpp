#include "header/ground.h"

Ground::Ground(Vector2 v, int layer) : RenderableEntity(v, layer){
    this->collisionLayer = layer;
}

Ground::Ground(Vector2 v, int layer, float hor, float vert, int dirx, int diry) : RenderableEntity(v, layer){
    this->collisionLayer = layer;
    this->horSpeed = hor;
    this->verSpeed = vert;
    this->dirx = dirx;
    this->diry = diry;
}

void Ground::update(Game *game){
    // TODO: Add proper sizing to the ground. Becomes important once the player can move off the screen.
	float delta = game->GetLastFrameTime();
	this->counter += 1;
	if (this->counter >= 120) {
		this->dirx = -(this->dirx);
		this->diry = -(this->diry);
		this->counter = 0;
	}
    DrawRectangleRec(Rectangle{this->pos.x += delta * this->horSpeed * this->dirx, this->pos.y += delta * this->verSpeed * this->diry, 1000.0f, 200.0f}, GRAY);
}

bool Ground::TouchGround(Player *target, float deltaTime){
    // TODO: Once again, account for the fact that we want variable sized grounds.
    Player *player = (Player *)target;
    return (this->collisionLayer  == player->GetLayer()) && this->pos.y <= player->GetPos().y;
    return (this->collisionLayer  == player->GetLayer()) &&
            this->pos.x           <= player->GetPos().x &&
            this->pos.x + 1000.0f >= player->GetPos().x &&
            this->pos.y           >= player->GetPos().y &&
            this->pos.y            < player->GetPos().y + player->GetCurrentVerticalSpeed() * deltaTime;
}
