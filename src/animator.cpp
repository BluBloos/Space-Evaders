#include "header/animator.h"

Animator::Animator(RenderableEntity* entity, Animation* entry){
    this->target = entity;
    this->currentAnimation = entry;
    this->frameCount = 0;
}

void Animator::PlayAnimation(){

    this->frameCount++;

    if (this->frameCount >= (60/this->currentAnimation->frameSpeed))
    {
        this->frameCount = 0;
        this->currentAnimation->currentFrame++;

        if (this->currentAnimation->currentFrame > (this->currentAnimation->frameNum - 1)) this->currentAnimation->currentFrame = 0;

        this->currentAnimation->frameRec.x = (float)this->currentAnimation->currentFrame*(float)this->currentAnimation->sprite.width/this->currentAnimation->frameNum;
    }

    DrawTextureRec(this->currentAnimation->sprite, this->currentAnimation->frameRec, this->target->GetPos(), WHITE);  // Draw part of the texture
}