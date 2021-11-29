#include "header/player.h"
#include "header/game.h"
#include "header/ground.h"

#include "animator.cpp"
#include <iostream>

<<<<<<< HEAD
Player::Player(Vector2 v, int layer) : RenderableEntity(v, layer){ 

=======
Player::Player(Vector2 v, int layer) : RenderableEntity(v, layer){
>>>>>>> 9d2b4ef4a73eeed5e1dae301d270585ea7d7106c
    this->currentVerticalSpeed = 0.0;
    this->inAir = true;
    this->flipMultiplier = 1;

    // Initialize Animator
    this->InitializeAnimations();                                                                     // Animator Example
    // Tell the animator what is the first animation to play when the game started.
    this->myAnimator = new Animator(this, &(this->animations.at(PLAYER_ANIMATIONSTART_NAME)));        // Animator Example
    this->SetConditions();  // Must be called after animator has been initialized!                    // Animator Example
    this->SetTransitions();                                                                           // Animator Example
}

void Player::update(Game *game){

    float deltaTime = game->GetLastFrameTime();

    // Handle the horizontal movement of player
    float dir = 0.0f;
<<<<<<< HEAD
    if (IsKeyDown(KEY_A)) {
        dir = -1.0f;
        this->myAnimator->FlipAnimation(LEFT);
        this->myAnimator->SetBool(PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE, true);   // Animator Example
    }
    else if (IsKeyDown(KEY_D)) {
        dir = 1.0f;
        this->myAnimator->FlipAnimation(RIGHT);
        this->myAnimator->SetBool(PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE, true);   // Animator Example
    }
    else {
        this->myAnimator->SetBool(PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE, false);  // Animator Example
    }
    this->run(deltaTime, dir); 
=======
    if (IsKeyDown(KEY_A)) {dir = -1.0f;}
    if (IsKeyDown(KEY_D)) {dir = 1.0f;}
    this->run(deltaTime, dir);
>>>>>>> 9d2b4ef4a73eeed5e1dae301d270585ea7d7106c

    // Code for the jumping routine.
    if (IsKeyDown(KEY_SPACE) && !this->inAir) {
        this->inAir = true;
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
            if (ground->TouchGround(this, deltaTime) && this->currentVerticalSpeed >= 0){
                // The player has collided with the ground. Stop movement.
            	this->inAir = false;
                this->currentVerticalSpeed = 0.0f;
                this->pos.y = ground->GetPos().y - this->animations.at(PLAYER_ANIMATIONSTART_NAME).sprite.height; // snap the y position of the player.

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
    }

    // Update the vertical movement of the player, note the flip multiplier.
    if (this->inAir) {
        this->pos.y += this->currentVerticalSpeed * deltaTime * flipMultiplier;
        this->currentVerticalSpeed += this->currentVerticalSpeed < 0 ? Entity::gravity * deltaTime : Entity::gravity * deltaTime * 1.5f;
    }

<<<<<<< HEAD
    this->myAnimator->PlayAnimation();
=======
    // Gravity function of the player
    if (IsKeyDown(KEY_G)) {
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
>>>>>>> 9d2b4ef4a73eeed5e1dae301d270585ea7d7106c
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
<<<<<<< HEAD

#pragma region Initialize Animator Components
void Player::InitializeAnimations(){
    // Stand
    Texture2D temp = LoadTexture(PLAYER_ANIMATIONSTART_PATH);
    Animation animTemp = {temp,     // Animation Frames
                          Rectangle{0.0f, 0.0f, (float)temp.width/24, (float)temp.height}, // Size of one frame 
                          RIGHT,    // The direction that the image faces to
                          0,        // Which frame is the first frame of the animation
                          0,        // Which frame starts to play at the first round. Usually same as the last one.
                          48,       // The number of frames that one frame of the sprite can stay. So-called frame speed.
                          24        // The total number of frames that the sprite has.
                          };      
    this->animations.insert({PLAYER_ANIMATIONSTART_NAME, animTemp});

    // Walk
    temp = LoadTexture(PLAYER_ANIMATION_WALK_PATH);
    this->animations.insert({PLAYER_ANIMATION_WALK_NAME, {temp, Rectangle{0.0f, 0.0f, (float)temp.width/28, (float)temp.height}, RIGHT, 0, 0, 120, 28}});
}

void Player::SetTransitions(){
    Animator::SetTransition(
        &this->animations[PLAYER_ANIMATIONSTART_NAME],    // From this animation
        &this->animations[PLAYER_ANIMATION_WALK_NAME],    // To this animation
        std::vector<TargetCondition>{                     // under these conditions
            Animator::SetBoolTargetCondition(PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE, true)
        }
    );
    Animator::SetTransition( 
        &this->animations[PLAYER_ANIMATION_WALK_NAME],  
        &this->animations[PLAYER_ANIMATIONSTART_NAME],     
        std::vector<TargetCondition>{                     
            Animator::SetBoolTargetCondition(PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE, false)
        }
    );
}

// The player has these flags to control the animation flow
// Initialize flags
void Player::SetConditions(){
    if (this->myAnimator) {
        this->myAnimator->SetIntCondition(PLAYER_ANIMATIONCONDITION_INT_NAME_ONE);
        this->myAnimator->SetBoolCondition(PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE);
        this->myAnimator->SetTriggerCondition(PLAYER_ANIMATIONCONDITION_TRIGGER_NAME_ONE);
    }
    else {
        TraceLog(LOG_ERROR, "Error: Animator has not been initialized!");
    }
}
#pragma endregion
=======
>>>>>>> 9d2b4ef4a73eeed5e1dae301d270585ea7d7106c
