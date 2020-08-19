#include "componentsystems/AnimatedComponentSystem.h"

#include <map>

#include "objects/components/AnimatedComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "utilities/StringHelpers.h"
#include "utilities/TIEMath.h"

using namespace TIE;

const std::string AnimatedComponentSystem::ANIMATED = "animated";
const std::string AnimatedComponentSystem::FRAMES = "frames";
const std::string AnimatedComponentSystem::RANGE = "range";
const std::string AnimatedComponentSystem::SPEED = "speed";
const std::string AnimatedComponentSystem::DIRECTION = "direction";

void AnimatedComponentSystem::update(const float delta) {
    for (auto c : this->components) {
        this->updateCurrentAnimation(c);
        if (this->progressAnimation(c.animatedComponent.getCurrentAnimation(), delta)) {
            this->setTextureRect(*c.animatedComponent.getCurrentAnimation(), c.spriteComponent);
        }
    }
}


void AnimatedComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {

	// Get all the keys containing animations from the stringValues map 
	std::vector<std::string> animatedStringKeys;
	for (auto i : factory.stringValues) {
		if (i.first.find("animated.") != std::string::npos) {
			animatedStringKeys.push_back(i.first);
		}
	}
    
	std::vector<std::string> animatedFloatKeys;
	for (auto i : factory.floatValues) {
		if (i.first.find("animated.") != std::string::npos) {
			animatedFloatKeys.push_back(i.first);
		}
	}

    if (animatedStringKeys.size()) {
        AnimatedComponent& animatedComponent = tientity.addComponent<AnimatedComponent>();
        SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
        MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
        
        if (spriteComponent == nullptr || movesComponent == nullptr) {
            return;
        }
        Components components = { animatedComponent, *spriteComponent, *movesComponent };

        std::map<std::string, Animation> animations;
        for (auto key : animatedStringKeys) {
            std::vector<std::string> parts;
            String::split(key, '.', parts);
            std::string animationName = parts.at(1);
            std::string animationField = parts.at(2);
			std::string value = factory.stringValues.at(key);

            if (!animations.count(animationName)) {
                animations[animationName] = Animation();
                animations[animationName].frames = std::vector<AnimationFrame>();
            }
            
            if (animationField == AnimatedComponentSystem::RANGE) {
                animations[animationName].range = String::stringToVector2f(value);
            } else if (animationField == AnimatedComponentSystem::FRAMES) {
                AnimationFrame animationFrame = AnimationFrame();
                animationFrame.rect = String::stringToIntRect(value);
                animations[animationName].frames.push_back(animationFrame);
            }
        }

        for (auto key : animatedFloatKeys) {
            std::vector<std::string> parts;
            String::split(key, '.', parts);
            std::string animationName = parts.at(1);
            std::string animationField = parts.at(2);
			float value = factory.floatValues.at(key);

            if (!animations.count(animationName)) {
                animations[animationName] = Animation();
                animations[animationName].frames = std::vector<AnimationFrame>();
            }

            if (animationField == AnimatedComponentSystem::SPEED) {
                animations[animationName].speed = value;
            } else if (animationField == AnimatedComponentSystem::DIRECTION) {
                animations[animationName].direction = value;
            }
        }

        animatedComponent.setAnimations(animations);
        this->updateCurrentAnimation(components);
        this->components.push_back(components);
    }

    return;
}


void AnimatedComponentSystem::updateCurrentAnimation(Components& components) {

        // float rotation = movesComponent->getVelocity().y;
        float rotation = components.spriteComponent.getRotation();
        std::map<std::string, Animation> animations = components.animatedComponent.getAnimations();
        for (auto animation : animations) {
            if (Math::isAngleBetweenAngles(rotation, animation.second.range.x, animation.second.range.y)) {
                animation.second.currentFrame = animation.second.frames.begin();
                components.animatedComponent.setCurrentAnimation(animation.second);
                this->setTextureRect(animation.second, components.spriteComponent);
                break;
            }
        }
}


bool AnimatedComponentSystem::progressAnimation(Animation* animation, const float delta) {
    if (animation != nullptr && animation->frames.size() > 1) {
        animation->elapsedTime += delta;
        if (animation->elapsedTime > animation->speed) {
            if (animation->currentFrame == animation->frames.end()) {
                animation->currentFrame = animation->frames.begin();
            }
            animation->currentFrame++;
            animation->elapsedTime = 0;
            return true;
        }
    }
    return false;
}


void AnimatedComponentSystem::setTextureRect(const Animation& animation, SpriteComponent& spriteComponent) {
    sf::IntRect rect = animation.currentFrame.operator*().rect;
    spriteComponent.setTextureRect(rect);
    spriteComponent.setOrigin(rect.width / 2, rect.height / 2);
    spriteComponent.setScale(animation.direction, 1);
}
