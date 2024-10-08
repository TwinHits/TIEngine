#include "componentsystems/AnimatedComponentSystem.h"

#include <map>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "managers/ComponentSystemsManager.h"
#include "utils/String.h"
#include "utils/TIEMath.h"

using namespace TIE;

AnimatedComponentSystem::AnimatedComponentSystem() {
    this->setName(AnimatedComponentSystem::ANIMATED);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(AnimatedComponentSystem::FRAMES, this);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(AnimatedComponentSystem::RANGE, this);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(AnimatedComponentSystem::SPEED, this);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(AnimatedComponentSystem::DIRECTION, this);
}


void AnimatedComponentSystem::update(const float delta) {
    for (auto& c : this->components) {
        this->updateCurrentAnimation(c.animatedComponent, c.positionComponent, c.spriteComponent);
        if (this->progressAnimation(c.animatedComponent.getCurrentAnimation(), delta)) {
            this->setTextureRect(*c.animatedComponent.getCurrentAnimation(), c.spriteComponent);
        }
    }
}


AnimatedComponent& AnimatedComponentSystem::addComponent(TIEntity& tientity) {
    if (!tientity.hasComponent<AnimatedComponent>()) {
        AnimatedComponent& animatedComponent = tientity.addComponent<AnimatedComponent>();
        PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
        SpriteComponent& spriteComponent = SpriteComponentSystem::Instance()->addComponent(tientity);
        this->components.push_back({ animatedComponent, positionComponent, spriteComponent });
        return animatedComponent;
    } else {
        return *tientity.getComponent<AnimatedComponent>();
    }

}


AnimatedComponent& AnimatedComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    AnimatedComponent& animatedComponent = this->addComponent(tientity);
    const ScriptTableReader& reader = factory.getReader().getReader(AnimatedComponentSystem::ANIMATED);

    for (auto& [animationName, animationReader] : reader.getReaders()) {
        std::map<std::string, Animation>& animations = animatedComponent.getAnimations();
        for (auto& [animationField, value] : animationReader.getValues<std::string>()) {

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

        for (auto& [animationField, value] : animationReader.getValues<float>()) {

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
    }

    return animatedComponent;
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


void AnimatedComponentSystem::updateCurrentAnimation(AnimatedComponent& animatedComponent, PositionComponent& positionComponent, SpriteComponent& spriteComponent) {
    float rotation = positionComponent.rotation;

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
    spriteComponent.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
    spriteComponent.setScale(animation.direction, 1);
}

