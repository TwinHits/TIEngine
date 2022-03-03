#include "componentsystems/PositionComponentSystem.h"

#include <string>
#include <math.h>

#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"

using namespace TIE;

void PositionComponentSystem::update(const float delta) {
    for (auto& c : this->components) {
        c.positionComponent.worldPosition = this->getWorldPosition(c.tientity);
        if (c.positionComponent.rotates) {
            c.positionComponent.worldRotation = this->getWorldRotation(c.tientity);
        }
    }
}


bool PositionComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    return false;
}


bool PositionComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    return false;
}


bool PositionComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity)  {
    return false;
}


void PositionComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
    Components components = { positionComponent, tientity };
    this->components.push_back(components);

	float x = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::X, positionComponent.position.x, tientity);
	float y = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::Y, positionComponent.position.y, tientity);
	float rotation = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::ROTATION, positionComponent.rotation, tientity);
	bool rotates = ComponentSystems::getFactoryValue<bool>(factory, PositionComponentSystem::ROTATES, positionComponent.rotates, tientity);

    positionComponent.position.x = x;
    positionComponent.position.y = y;
    positionComponent.rotation = rotation;
    positionComponent.rotates = rotates;
}


bool PositionComponentSystem::removeComponent(TIEntity& tientity) {
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
	if (positionComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->positionComponent == positionComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<PositionComponent>();
	} else {
		return false;
	}
}


const std::string& PositionComponentSystem::getName() {
    return PositionComponentSystem::POSITION;
}


void PositionComponentSystem::setPosition(TIEntity& tientity, float x, float y) {
    PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
    if (positionComponent != nullptr) {
        positionComponent->position.x = x;
        positionComponent->position.y = y;
    }
}


void PositionComponentSystem::setRotation(TIEntity& tientity, float rotation) {
    PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
    if (positionComponent != nullptr) {
        positionComponent->rotation = rotation;
    }
}


sf::Vector2f PositionComponentSystem::getWorldPosition(TIEntity& tientity) {
    sf::Vector2f worldPosition = sf::Vector2f();

    for (TIEntity* t = &tientity; t != nullptr; t = &t->getParent()) {
        PositionComponent* component = t->getComponent<PositionComponent>();
        if (component != nullptr) {
            PositionComponent* parentComponent = t->getParent().getComponent<PositionComponent>();
            if (parentComponent != nullptr && component->rotates) {
                // If the parent has a position, then rotate the child's position by the parent's rotation to stay oriented around parent's origin
                worldPosition += Math::rotateVectorByAngle(component->position, parentComponent->rotation);
            } else { 
                worldPosition += component->position;
            }
        }
    }

    return worldPosition;
}


float PositionComponentSystem::getWorldRotation(TIEntity& tientity) {
    float rotation = 0;

    for (TIEntity* t = &tientity; t != nullptr; t = &t->getParent()) {
        PositionComponent* component = t->getComponent<PositionComponent>();
        if (component != nullptr) {
            rotation += component->rotation;
        }
    }

    return rotation;
}

sf::Transform PositionComponentSystem::getWorldTransform(TIEntity& tientity) {
        sf::Transform transform = sf::Transform::Identity;

        for (TIEntity* t = &tientity; t != nullptr; t = &t->getParent()) {
            SpriteComponent* component = t->getComponent<SpriteComponent>();
            if (component != nullptr) {
                transform *= component->getTransform();
            }
        }

        return transform;
}
