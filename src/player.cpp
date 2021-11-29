#include "header/player.h"
#include "header/game.h"
#include "header/ground.h"
#include "header/enemy.h"
#include "animator.cpp"
#include <iostream>

Player::Player(Vector2 v, int layer) : Character(v, layer){
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
    if (game->getControlFlag()) {
        if (IsKeyDown(KEY_A)) {dir = -1.0f;}
        if (IsKeyDown(KEY_D)) {dir = 1.0f;}
    }

    else {
        if (IsKeyDown(KEY_LEFT)) {dir = -1.0f;}
        if (IsKeyDown(KEY_RIGHT)) {dir = 1.0f;}
    }

    if (dir == -1.0f) {
        this->myAnimator->FlipAnimation(LEFT);
        this->myAnimator->SetBool(PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE, true);   // Animator Example
    }
    else if (dir == 1.0f) {
        this->myAnimator->FlipAnimation(RIGHT);
        this->myAnimator->SetBool(PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE, true);   // Animator Example
    }
    else {
        this->myAnimator->SetBool(PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE, false);  // Animator Example
    }

    this->run(deltaTime, dir); 

    

    // Code for the gravity flip routine.
    /*if (IsKeyDown(KEY_F) && !this->inAir) {
        this->gravityFlip();
    }*/

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
                //this->pos.y = ground->GetPos().y - this->animations.at(PLAYER_ANIMATIONSTART_NAME).sprite.height; // snap the y position of the player.
                this->pos.y = ground->GetPos().y;
                break;
            } else {
                this->inAir = true;
            }
        }

        // Check if player has collided with any enemies
        std::vector<Entity *> enemies = game->GetCharacters();
		for (unsigned int i = 1; i < enemies.size(); i++) {
			Enemy *enemy = (Enemy *)enemies[i];
			if (enemy->EnemyCollide(this)){
				// TODO: Change code to procedure for ending game once task is completed
				this->inAir = false;
				this->currentVerticalSpeed = 0.0f;
				this->pos.y = enemy->GetPos().y; // snap the y position of the player.
				break;
			}
		}


        // TODO: Check if the player is touching the sides of the screen.
        if (this->pos.x < 0) {
            this->pos.x = 0; // Snap the player.
        }
        if (this->pos.x > 3950) {
            // TODO: Change 850 from a constant to something that is dependent on a variable screen size.
            this->pos.x = 3950;
        }
        // TODO: Check if player is touching top or bottom of the screen, in which case, send them back to spawn (?).
    }

    // Code for the jumping routine.
    // NOTE(Noah): Moved the jumping routine below so that we don't snap the player back to the platform right away...
    if (IsKeyDown(KEY_SPACE) && !this->inAir) {
        this->jump();
    }

    // Update the vertical movement of the player, note the flip multiplier.
    if (this->inAir) {
        this->pos.y += this->currentVerticalSpeed * deltaTime * flipMultiplier;
        this->currentVerticalSpeed += Entity::gravity * deltaTime;
    }

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

    this->myAnimator->PlayAnimation();
}

void Player::run(float delta, float direction){
    this->pos.x += direction * delta * this->horSpeed;
}

void Player::jump(){
    this->currentVerticalSpeed = - sqrtf(Entity::gravity * 2 * 160); // 160 has units of pixels. Setting V0 for max jump height of 160.
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
    /* NOTE(Noah): 
        Given that we are doing this type of hard coding for the initialization of animations
        I am going to continue on this trend. We need to subsample into each animation rectangle because each sprite is 
        a much smaller width than the actual rectangle.
        And we will need to do this for both the standing and walking animations.
    */ 
   int STAND_PIXEL_WIDTH = 19;
   int STAND_PIXEL_LEFT_OFFSET = 93;
   int STAND_IMAGES = 24;
   int WALK_PIXEL_WIDTH = 24;
   int WALK_PIXEL_OFFSET = 95;
    
    // Stand
    Texture2D temp = LoadTexture(PLAYER_ANIMATIONSTART_PATH);
    Animation animTemp = {temp,     // Animation Frames
                          Rectangle{(float)STAND_PIXEL_LEFT_OFFSET, 0.0f, (float)STAND_PIXEL_WIDTH, (float)temp.height}, // Size of one frame 
                          RIGHT,    // The direction that the image faces to
                          0,        // Which frame is the first frame of the animation
                          0,        // Which frame starts to play at the first round. Usually same as the last one.
                          48,       // The number of frames that one frame of the sprite can stay. So-called frame speed.
                          24,        // The total number of frames that the sprite has.
                          temp.width/24, // stride to step frame rectangle by 
                          STAND_PIXEL_LEFT_OFFSET
                          };      
    this->animations.insert({PLAYER_ANIMATIONSTART_NAME, animTemp});

    // Walk
    temp = LoadTexture(PLAYER_ANIMATION_WALK_PATH);
    this->animations.insert({PLAYER_ANIMATION_WALK_NAME, {temp, Rectangle{(float)WALK_PIXEL_OFFSET, 0.0f, (float)WALK_PIXEL_WIDTH, (float)temp.height}, 
        RIGHT, 
        0, // first frame
        0, // first frame, first round
        120, // frame wait time (defines rate animation plays)
        28, // frames
        temp.width/28,
        WALK_PIXEL_OFFSET}});
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
