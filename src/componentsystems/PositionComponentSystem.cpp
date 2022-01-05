#include <string>

#include "objects/components/PositionComponent.h"
#include "componentsystems/PositionComponentSystem.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

void PositionComponentSystem::update(const float delta) {}


void PositionComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	float x = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::X, 0.0F, tientity);
	float y = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::Y, 0.0F, tientity);
	float angle = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::ANGLE, 0.0F, tientity);

	if (x || y || angle) {
		PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
		Components components = { positionComponent };

		positionComponent.position.x = x;
		positionComponent.position.y = y;
		positionComponent.angle = angle;

		this->components.push_back(components);
	}
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
