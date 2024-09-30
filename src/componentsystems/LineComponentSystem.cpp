#include "componentsystems/LineComponentSystem.h" 

#include "componentsystems/PositionComponentSystem.h" 
#include "componentsystems/WireframeComponentSystem.h" 
#include "managers/ComponentSystemsManager.h"
#include "managers/ScriptManager.h"
#include "utils/TIEMath.h"

using namespace TIE;

LineComponentSystem::LineComponentSystem() {
	this->setName(LineComponentSystem::LINE);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(LineComponentSystem::MAGNITUDE, this);
}


void LineComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		this->setLine(c.lineComponent, c.positionComponent);
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
	const ScriptTableReader& reader = factory.getReader().getReader(LineComponentSystem::LINE);

	const float& magnitude = reader.get<float>(LineComponentSystem::MAGNITUDE, lineComponent.getMagnitude());
	lineComponent.setMagnitude(magnitude);

	this->setLine(lineComponent, positionComponent);

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
		this->setLine(component, tientity);
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


void LineComponentSystem::setLine(TIEntity& tientity) {
	if (tientity.hasComponent<LineComponent>() && tientity.hasComponent<PositionComponent>()) {
		this->setLine(*tientity.getComponent<LineComponent>(), *tientity.getComponent<PositionComponent>());
	}
}


void LineComponentSystem::setLine(LineComponent& lineComponent, TIEntity& tientity) {
	if (tientity.hasComponent<PositionComponent>()) {
		this->setLine(lineComponent, *tientity.getComponent<PositionComponent>());
	}
}


void LineComponentSystem::setLine(LineComponent& lineComponent, PositionComponent& positionComponent) {
    sf::VertexArray line = sf::VertexArray(sf::Points, 2);
    line[0] = positionComponent.worldPosition;
    line[1] = line[0].position + Math::translateVelocityByTime(sf::Vector2f(lineComponent.getMagnitude(), positionComponent.worldRotation), 1);
    lineComponent.setLine(line);
}


std::pair<GlobalId, GlobalId> LineComponentSystem::addWireframe(TIEntity& tientity) {
	LineComponent* component = tientity.getComponent<LineComponent>();
	if (component) {
		PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
		return WireframeComponentSystem::Instance()->createWireframe(tientity, sf::FloatRect(0,0,component->getMagnitude(), 0), positionComponent->position, positionComponent->rotation);
	}
	return std::pair(0,0);
}
