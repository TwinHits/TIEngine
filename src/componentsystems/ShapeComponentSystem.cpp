#include "componentsystems/ShapeComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/ShapeComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void ShapeComponentSystem::update(const float delta) {

}


void ShapeComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

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


const std::string& ShapeComponentSystem::getName() {
	return ShapeComponentSystem::SHAPE;
}
