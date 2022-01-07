#include "componentsystems/PositionComponentSystem.h"

#include <string>

#include "objects/components/PositionComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

void PositionComponentSystem::update(const float delta) {}


void PositionComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
    Components components = { positionComponent };
    this->components.push_back(components);

	float x = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::X, 0.0F, tientity);
	float y = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::Y, 0.0F, tientity);
	float rotation = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::ROTATION, 0.0F, tientity);

    positionComponent.position.x = x;
    positionComponent.position.y = y;
    positionComponent.rotation = rotation;
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


sf::Transform PositionComponentSystem::getWorldTransform(TIEntity& tientity) {
    sf::Transform transform = sf::Transform::Identity;

    for (TIEntity* t = &tientity; t != nullptr; t = &t->getParent()) {
        PositionComponent* component = t->getComponent<PositionComponent>();
        if (component != nullptr) {
            transform = transform.translate(component->position);
        }
    }

    return transform;
}


sf::Vector2f PositionComponentSystem::getWorldPosition(TIEntity& tientity) {
    return getWorldTransform(tientity) * sf::Vector2f();
}


float PositionComponentSystem::getWorldRotation(TIEntity& tientity) {
    float rotation = 0;

    for (TIEntity* t = &tientity; t != nullptr; t = &t->getParent()) {
        PositionComponent* component = t->getComponent<PositionComponent>();
        if (component != nullptr) {
            rotation += component->rotation;
        }
    }

    PositionComponent* component = tientity.getComponent<PositionComponent>();
    if (component != nullptr) {
        rotation += component->rotation;
    }

    return rotation;
}
