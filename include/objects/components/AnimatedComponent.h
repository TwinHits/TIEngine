#ifndef ANIMATEDCOMPONENT_H
#define ANIMATEDCOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

namespace TIE {

struct AnimationFrame {
    sf::IntRect rect;
    int mirror = 1;
};


struct Animation {
    std::vector<AnimationFrame> frames;
    std::vector<AnimationFrame>::iterator currentFrame = frames.end();
    sf::Vector2f range = sf::Vector2f(0, 0);
    float speed = 0;
    float elapsedTime = 0;
    int direction = 1;
};


class AnimatedComponent : public Component {
    public:
        void setAnimations(std::map<std::string, Animation>);
        std::map<std::string, Animation>& getAnimations();
        
        void setCurrentAnimation(Animation&);
        Animation* getCurrentAnimation();
    private:
        std::map<std::string, Animation> animations;
        Animation* currentAnimation = nullptr;
};

}

#endif