#include "componentsystems/LineComponentSystem.h" 

#include <sol/sol.hpp>
#include "SFML/Graphics.hpp"

#include <string>

#include "componentsystems/PositionComponentSystem.h" 
#include "managers/ScriptManager.h"
#include "objects/components/LineComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"

using namespace TIE;

LineComponentSystem::LineComponentSystem() {
	this->setName(LineComponentSystem::LINE);
	ComponentSystems::insertComponentPropertyIntoMap(LineComponentSystem::MAGNITUDE, this->componentPropertyMap);
}


void LineComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		sf::VertexArray line = sf::VertexArray(sf::Lines, 2);
		line[0] = c.positionComponent.worldPosition;
		line[1] = line[0].position + Math::translateVelocityByTime(sf::Vector2f(c.lineComponent.getMagnitude(), c.positionComponent.worldRotation), 1);
		c.lineComponent.setLine(line);
	}
}


LineComponent& LineComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<LineComponent>()) {
        LineComponent& lineComponent = tientity.addComponent<LineComponent>();
        PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
        this->components.push_back({ lineComponent, positionComponent });
        return lineComponent;
	} else {
		return *tientity.getComponent<LineComponent>();
	}
}


LineComponent& LineComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	LineComponent& lineComponent = this->addComponent(tientity);
	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);

	float magnitude = ComponentSystems::getFactoryValue<float>(factory, LineComponentSystem::MAGNITUDE, lineComponent.getMagnitude(), tientity);
	lineComponent.setMagnitude(magnitude);

	return lineComponent;
}


bool LineComponentSystem::removeComponent(TIEntity& tientity) {
	LineComponent* lineComponent = tientity.getComponent<LineComponent>();
	if (lineComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->lineComponent == lineComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<LineComponent>();
	} else {
		return false;
	}
}


void LineComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
	LineComponent& component = this->addComponent(tientity);
	if (key == LineComponentSystem::MAGNITUDE) {
		component.setMagnitude(value);
	}
}


sol::object LineComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	LineComponent* component = tientity.getComponent<LineComponent>();
	if (component) {
		if (key == LineComponentSystem::MAGNITUDE) {
			return ScriptManager::Instance()->getObjectFromValue(component->getMagnitude());
		}
    }
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}
