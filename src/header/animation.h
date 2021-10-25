#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib_wrapped.h"
#include <string>

struct Animation{

    // Frames of the Animation
    Texture2D sprite;
    // To allocate which frame of the sprite is displayed
    Rectangle frameRec;

    // Which Frame is displayed now
    int currentFrame;
    // The number of frames that one frame of the sprite can stay.
    int frameSpeed;
    // The number of frames that the sprite has.
    int frameNum;
};
#endif