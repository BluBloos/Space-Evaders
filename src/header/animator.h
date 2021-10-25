#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "entity.h"
#include "animation.h"
#include <vector>

class Animator{
    public:
        Animator(RenderableEntity*, Animation*);
        void PlayAnimation();
    private:
        RenderableEntity* target;
        Animation* currentAnimation;
        int frameCount;
};

#endif