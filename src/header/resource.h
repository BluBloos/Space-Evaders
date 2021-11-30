#ifndef RESOURCE_H
#define RESOURCE_H

/*
 * Highly Recommand to define constants for each file resource and names of files and certain variables
 */

// Screen Size (Camera Size)
#define SCREENWIDTH 850
#define SCREENHEIGHT 600
// Because origin of the image is at upper-left corner, the offset value of cameras should be corrected.
#define OFFSETCORRECTVALUE 100.0f
// Animation file path and animation name
#define PLAYER_ANIMATIONSTART_PATH "../arts/stand.png"
#define PLAYER_ANIMATIONSTART_NAME "Stand"
#define PLAYER_ANIMATION_WALK_PATH "../arts/walk.png"
#define PLAYER_ANIMATION_WALK_NAME "Walk"
// Flags used by the player
#define PLAYER_ANIMATIONCONDITION_INT_NAME_ONE "intOne"
#define PLAYER_ANIMATIONCONDITION_BOOL_NAME_ONE "boolOne"
#define PLAYER_ANIMATIONCONDITION_TRIGGER_NAME_ONE "triggerOne"

#endif
