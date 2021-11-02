#include "header/player.h"
#include "header/game.h"
#include "header/ground.h"
#include "header/gameover.h"
#include <iostream>


Player::Player(Vector2 v, int layer) : RenderableEntity(v, layer){
    this->currentVerticalSpeed = 0.0;
    this->inAir = true;
    this->flipMultiplier = 1;
    this->alive = true;
}

void Player::update(Game *game){

    float deltaTime = game->GetLastFrameTime();

    // Handle the horizontal movement of player
    float dir = 0.0f;
    if (IsKeyDown(KEY_A && this->alive)) {dir = -1.0f;}
    if (IsKeyDown(KEY_D && this->alive)) {dir = 1.0f;}
    this->run(deltaTime, dir);

    // Code for the jumping routine.
    if (IsKeyDown(KEY_SPACE) && !this->inAir && this->alive) {
        this->inAir = true;
        this->jump();
    }

    // Code for the gravity flip routine.
    if (IsKeyDown(KEY_F) && !this->inAir && this->alive) {
        this->gravityFlip();
    }

    // Player collision code
    {
        // Check if the player has hit any ground
        std::vector<Entity *> grounds = game->GetGrounds();
        for (unsigned int i = 0; i < grounds.size(); i++) {
            Ground *ground = (Ground *)grounds[i];
            if (ground->TouchGround(this, deltaTime) && this->currentVerticalSpeed >= 0){
                // The player has collided with the ground. Stop movement.
            	this->inAir = false;
                this->currentVerticalSpeed = 0.0f;
                this->pos.y = ground->GetPos().y; // snap the y position of the player.
                break;
            } else {
            	this->inAir = true;
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

        if (this->pos.y <= 0){ //player has fell off the world -> kill them
            gameover gg(); //creates an instance of the gameover class which will create a rectangle until
            }
    }

    // Update the vertical movement of the player, note the flip multiplier.
    if (this->inAir) {
        this->pos.y += this->currentVerticalSpeed * deltaTime * flipMultiplier;
        this->currentVerticalSpeed += this->currentVerticalSpeed < 0 ? Entity::gravity * deltaTime : Entity::gravity * deltaTime * 1.5f;
    }

    // Gravity function of the player
    if (IsKeyDown(KEY_G  && this->alive)) {
        // Activate the black hole and move all platforms to the player.
        std::vector<Entity *> grounds = game->GetGrounds();
        for (unsigned int i = 0; i < grounds.size(); i++) { 
            Ground *ground = (Ground *)grounds[i];
            if (ground->IsMovable()) {

                Vector2 groundPos = ground->GetPos();

                // Generate vector from ground to player (this is the vector to apply gravity in).
                Vector2 gravityDirection;
                gravityDirection.x = this->pos.x - groundPos.x;
                gravityDirection.y = this->pos.y - groundPos.y;

                // Normalize the gravity direction vector.
                gravityDirection = Vector2Normalize(gravityDirection);

                Vector2 gravityForce = Vector2Scale(gravityDirection, Entity::gravity * 10.0f);
                 
                ground->ApplyForce(gravityForce, deltaTime);
            }
        }
    }

    // Render the player using raylib DrawCircle function.
    DrawCircle(this->pos.x, this->pos.y, 50.0f, BLACK);
}

void Player::run(float delta, float direction){
    this->pos.x += direction * delta * this->horSpeed;
}

void Player::jump(){
    this->currentVerticalSpeed = -verSpeed;
}

float Player::GetCurrentVerticalSpeed(){
    return this->currentVerticalSpeed;
}

void Player::gravityFlip() {
    this->flipMultiplier = this->flipMultiplier * -1; // flip the multiplier
}
