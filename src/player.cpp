#include "header/player.h"
#include "header/game.h"
#include "header/ground.h"

#include "animator.cpp"
#include <iostream>

Player::Player(Vector2 v, int layer) : RenderableEntity(v, layer){ 

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
                this->pos.y = ground->GetPos().y - this->animations.at(PLAYER_ANIMATIONSTART_NAME).sprite.height; // snap the y position of the player.

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

void Player::gravityFlip() {
    this->flipMultiplier = this->flipMultiplier * -1; // flip the multiplier
}

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