#include "componentsystems/AnimatedComponentSystem.h"

#include <map>

#include "objects/components/AnimatedComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/StringHelpers.h"
#include "utils/TIEMath.h"

using namespace TIE;

void AnimatedComponentSystem::update(const float delta) {
    for (auto& c : this->components) {
        this->updateCurrentAnimation(c.animatedComponent, c.positionComponent, c.spriteComponent);
        if (this->progressAnimation(c.animatedComponent.getCurrentAnimation(), delta)) {
            this->setTextureRect(*c.animatedComponent.getCurrentAnimation(), c.spriteComponent);
        }
    }
}


void AnimatedComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {

	// Get all the keys containing animations from the stringValues map 
	std::vector<std::string> animatedStringKeys;
	for (auto& i : factory.stringValues) {
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
        PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
        SpriteComponent& spriteComponent = tientity.addComponent<SpriteComponent>();
        Components components = { animatedComponent, positionComponent, spriteComponent };

        std::map<std::string, Animation>& animations = animatedComponent.getAnimations();
        for (auto& key : animatedStringKeys) {
            std::vector<std::string> keyParts = String::slice(key, '.', 1);
            std::string animationName = keyParts.at(0);
            std::string animationField = keyParts.at(1);
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

        for (auto& key : animatedFloatKeys) {
            std::vector<std::string> keyParts = String::slice(key, '.', 1);
            std::string animationName = keyParts.at(0);
            std::string animationField = keyParts.at(1);
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

        for (auto& animation : animations) {
            animation.second.currentFrame = animation.second.frames.begin();
        }
        animatedComponent.setCurrentAnimation(animations.begin().operator*().second);
        this->components.push_back(components);
    }

    return;
}


bool AnimatedComponentSystem::removeComponent(TIEntity& tientity) {
    AnimatedComponent* animatedComponent = tientity.getComponent<AnimatedComponent>();
    if (animatedComponent != nullptr) {
        for (auto i = this->components.begin(); i != this->components.end(); ++i) {
            if (&i->animatedComponent == animatedComponent) {
                this->components.erase(i);
                break;
            }
        }
        return tientity.removeComponent<AnimatedComponent>();
    } else {
        return false;
    }
}


const std::string& AnimatedComponentSystem::getName() {
    return AnimatedComponentSystem::ANIMATED;
}


void AnimatedComponentSystem::updateCurrentAnimation(AnimatedComponent& animatedComponent, PositionComponent& positionComponent, SpriteComponent& spriteComponent) {
    float rotation = positionComponent.angle;

	if (animatedComponent.getCurrentAnimation() == nullptr || !Math::isAngleBetweenAngles(rotation, animatedComponent.getCurrentAnimation()->range.x, animatedComponent.getCurrentAnimation()->range.y)) {
		std::map<std::string, Animation>& animations = animatedComponent.getAnimations();
		for (auto& animation : animations) {
			if (Math::isAngleBetweenAngles(rotation, animation.second.range.x, animation.second.range.y)) {
				animation.second.currentFrame = animation.second.frames.begin();
				animatedComponent.setCurrentAnimation(animation.second);
				this->setTextureRect(animation.second, spriteComponent);
				break;
			}
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

