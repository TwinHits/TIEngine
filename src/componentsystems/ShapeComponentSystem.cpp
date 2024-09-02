#include "componentsystems/ShapeComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "objects/components/ShapeComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "managers/HashManager.h"
#include "managers/ScriptManager.h"
#include "utils/String.h"

using namespace TIE;

ShapeComponentSystem::ShapeComponentSystem() {
	this->setName(ShapeComponentSystem::SHAPE);
}


void ShapeComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		for (auto& [id, shape] : c.shapeComponent.getShapes()) {
			shape->setPosition(c.positionComponent.worldPosition);
			if (c.shapeComponent.isRotates()) {
				shape->setRotation(c.positionComponent.worldRotation);
			}
		}
	}
}


ShapeComponent& ShapeComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	return this->addComponent(tientity);
}


ShapeComponent& ShapeComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<ShapeComponent>()) {
		ShapeComponent& shapeComponent = tientity.addComponent<ShapeComponent>();
		PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
		this->components.push_back({ shapeComponent, positionComponent, tientity });
		return shapeComponent;
	} else {
		return *tientity.getComponent<ShapeComponent>();
	}
}


bool ShapeComponentSystem::removeComponent(TIEntity& tientity) {
	ShapeComponent* shapeComponent = tientity.getComponent<ShapeComponent>();
	if (shapeComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->shapeComponent == shapeComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<ShapeComponent>();
	} else {
		return false;
	}
}
