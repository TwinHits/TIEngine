#include "objects/components/AnimatedComponent.h"

using namespace TIE;

void AnimatedComponent::setAnimations(std::map<std::string, Animation> animations) {
    this->animations = animations;
}

std::map<std::string, Animation> AnimatedComponent::getAnimations() {
    return this->animations;
}


void AnimatedComponent::setCurrentAnimation(Animation& animation) {
    this->currentAnimation = &animation;
}


Animation* AnimatedComponent::getCurrentAnimation() {
    return this->currentAnimation;
}

