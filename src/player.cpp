#include "header/player.h"
#include "header/game.h"
#include "header/ground.h"

#include "animator.cpp"
#include <iostream>


Player::Player(Vector2 v, int layer) : RenderableEntity(v, layer){ 

    this->currentVerticalSpeed = 0.0;
    this->inAir = true;
    this->flipMultiplier = 1;

    this->InitializeAnimations();
    this->myAnimator = new Animator(this, &this->animations[0]);
}

void Player::update(Game *game){ 

    float deltaTime = game->GetLastFrameTime();

    // Handle the horizontal movement of player
    float dir = 0.0f;
    if (IsKeyDown(KEY_A)) {dir = -1.0f;}
    if (IsKeyDown(KEY_D)) {dir = 1.0f;}
    this->run(deltaTime, dir); 

    // Code for the jumping routine.
    if (IsKeyDown(KEY_SPACE) && !this->inAir) {
        this->jump();
    }

    // Code for the gravity flip routine.
    if (IsKeyDown(KEY_F) && !this->inAir) {
        this->gravityFlip();
    }

    // Player collision code
    {
        // Check if the player has hit any ground
        std::vector<Entity *> grounds = game->GetGrounds();
        for (unsigned int i = 0; i < grounds.size(); i++) { 
            Ground *ground = (Ground *)grounds[i];
            if (ground->TouchGround(this, deltaTime)){
                // The player has collided with the ground. Stop movement.
                this->inAir = false;
                this->currentVerticalSpeed = 0.0f;
                this->pos.y = ground->GetPos().y - this->animations[0].sprite.height; // snap the y position of the player.
                break;
            }
        }
        // TODO: Check if the player is touching the sides of the screen.
        if (this->pos.x < 0) {
            this->pos.x = 0; // Snap the player.
        }
        if (this->pos.x > 850) {
            // TODO: Change 850 from a constant to something that is dependent on a variable screen size.
            this->pos.x = 850;
        }
        // TODO: Check if player is touching top or bottom of the screen, in which case, send them back to spawn (?).
    }

    // Update the vertical movement of the player, note the flip multiplier.
    if (this->inAir) {
        this->pos.y += this->currentVerticalSpeed * deltaTime * flipMultiplier;
        this->currentVerticalSpeed += this->currentVerticalSpeed < 0 ? Entity::gravity * deltaTime : Entity::gravity * deltaTime * 1.5f;
    }

    this->myAnimator->PlayAnimation();
}

void Player::run(float delta, float direction){
    this->pos.x += direction * delta * this->horSpeed;
}

void Player::jump(){
    this->currentVerticalSpeed = -verSpeed;
    this->inAir = true;
}

float Player::GetCurrentVerticalSpeed(){
    return this->currentVerticalSpeed;
}

std::vector<Animation> Player::GetAnimations(){
    return this->animations;
}

void Player::gravityFlip() {
    this->flipMultiplier = this->flipMultiplier * -1; // flip the multiplier
}

void Player::InitializeAnimations(){

    

    Texture2D temp = LoadTexture("../arts/UI_Tip.png");
    Animation animTemp = {temp, Rectangle{0.0f, 0.0f, (float)temp.width/24, (float)temp.height}, 0, 48, 24};
    this->animations.push_back(animTemp);
}