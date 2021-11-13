#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "animation.h"
#include <unordered_map>
#include <string>

class RenderableEntity;

#pragma region Condition
/*
 * Difference between target condition and condition:
 * values of target condition should not be changed once initialized, but conditions will be changed based on the player movement
 * By comparing target condition with values of conditions, the program decides which animation to play
 * 
 * Similarity:
 * They use the same name (string type) to distinguish each other. One target condition and one condition shares one name.
 */
class Condition {
    public:
        Condition(){}
        Condition(FLAG f){
            this->flag = f;
        }
    
        FLAG flag;     // Redundant variable
};
class IntCondition : public Condition {
    public:
        IntCondition() : Condition(INTEGER){
            this->value = -999;
        }
        int value;
};
class BoolCondition : public Condition {
    public:
        BoolCondition() : Condition(BOOLEAN){
            this->value = false;
        }
        bool value;
};
class TriggerCondition : public Condition {
    public:
        TriggerCondition() : Condition(TRIGGER){
            this->value = false;
        }
        bool value;
};
#pragma endregion

class Animator{
    
    public:
        Animator(RenderableEntity*, Animation*);

        // main function, called by update()
        void PlayAnimation();
        // Used to set Flag values to control animation flow
        void SetInteger(const std::string&, int);
        void SetBool(const std::string&, bool);
        void SetTrigger(const std::string&);

        // Initialization functions
        // Assign the next animation to play
        static void SetTransition(Animation*, Animation*, std::vector<TargetCondition>);
        // These three functions should only be used when SetTransition is called.
        static TargetCondition SetIntTargetCondition(const std::string&, INTCONDITION, int);
        static TargetCondition SetBoolTargetCondition(const std::string&, bool);
        static TargetCondition SetTriggerTargetCondition(const std::string&);
        // SetCondition must be called after the animator object initialized.
        void SetIntCondition(const std::string&);
        void SetBoolCondition(const std::string&);
        void SetTriggerCondition(const std::string&);


    private:
        // attr
        RenderableEntity* target;
        Animation* currentAnimation;
        // The number of frames (in time) has stayed.
        int frameCount;
        std::vector<std::string> openTrigger;
        std::unordered_map<std::string, Condition*> conditions;
        // func
        // Go through all flags and check out what the next animation is.
        void checkTransition(); 
        // When the animation is changed, data on controling frame number have to be changed
        void resetAnimationConfig();
        // Reset trigger value automatically
        void resetTrigger();
};

#endif