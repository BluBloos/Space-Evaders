#include "header/player.h"
#include "header/game.h"
#include "header/ground.h"
#include <iostream>


Player::Player(Vector2 v, int layer) : RenderableEntity(v, layer){ 
    this->curVerSpeed = 0.0;
    this->canJump = false;
    this->touchGround = false;
}

void Player::update(){

    float deltaTime = GetFrameTime();

    this->run(deltaTime);
    this->jump(deltaTime);

    DrawCircle(this->pos.x, this->pos.y, 50.0f, BLACK);
}

void Player::run(float delta){
    if (IsKeyDown(KEY_A)) this->pos.x -= delta*this->horSpeed;
    if (IsKeyDown(KEY_D)) this->pos.x += delta*this->horSpeed;
}

void Player::jump(float delta){
    if (IsKeyDown(KEY_SPACE) && this->canJump){ 
        this->curVerSpeed = -verSpeed;
        this->canJump = false;
    }

    for (Entity *ground : grounds) {
        if (((Ground*)ground)->TouchGround(this, delta)){
            this->curVerSpeed = 0.0f;
            this->pos.y = ground->GetPos().y;
            this->canJump = true;            
            this->touchGround = true;
            break;
        }
        touchGround = false;
    }

    if (!touchGround) {
        this->pos.y += this->curVerSpeed*delta;
        this->canJump = false;
        this->curVerSpeed += this->curVerSpeed < 0 ? Entity::gravity*delta : Entity::gravity*delta*1.5f;
    }
}

float Player::GetCurVerSpeed(){
    return this->curVerSpeed;
}