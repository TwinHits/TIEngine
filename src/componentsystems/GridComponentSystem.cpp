#include "componentsystems/GridComponentSystem.h"

#include <SFML/Graphics.hpp>
 
#include "componentsystems/SpriteComponentSystem.h"
#include "managers/WorldManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"

using namespace TIE;

void GridComponentSystem::update(const float) {

}

GridComponent& GridComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<GridComponent>()) {
		GridComponent& gridComponent = tientity.addComponent<GridComponent>();
		SpriteComponent& spriteComponent = SpriteComponentSystem::Instance()->addComponent(tientity);
		this->components.push_back({ gridComponent, spriteComponent });
		return gridComponent;
	} else {
		return *tientity.getComponent<GridComponent>();
	}
}


GridComponent& GridComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {
	GridComponent& gridComponent = this->addComponent(entity);
	SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();

    float width = factory.floatValues.at(GridComponentSystem::WIDTH);
    float height = factory.floatValues.at(GridComponentSystem::HEIGHT);
    gridComponent.setGridSize(sf::Vector2i(width, height));

    sf::FloatRect textureSize = spriteComponent.getLocalBounds();
    gridComponent.setTileSize(sf::Vector2f(textureSize.width / width, textureSize.height / height));

	return gridComponent;
}


bool GridComponentSystem::removeComponent(TIEntity& tientity) {
	GridComponent* gridComponent = tientity.getComponent<GridComponent>();
	if (gridComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->gridComponent == gridComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<GridComponent>();
	} else {
		return false;
	}
}


const std::string& GridComponentSystem::getName() {
	return GridComponentSystem::GRID;
}


bool GridComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    return false;
}


bool GridComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    return false;
}


bool GridComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity)  {
    return false;
}


sol::object GridComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


ComponentSystems::ComponentSystemPropertiesMap& GridComponentSystem::populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap& map) {
	ComponentSystems::insertComponentPropertyIntoMap(GridComponentSystem::WIDTH, map);
	ComponentSystems::insertComponentPropertyIntoMap(GridComponentSystem::HEIGHT, map);
	return map;
}


sf::Vector2f GridComponentSystem::normalizePositionToGrid(const sf::Vector2f& position) {
	if (WorldManager::Instance()->isGridConfigured()) {
		TIEntity* levelEntity = WorldManager::Instance()->getLevelEntity();
		GridComponent* gridComponent = levelEntity->getComponent<GridComponent>();
		SpriteComponent* spriteComponent = levelEntity->getComponent<SpriteComponent>();
		if (gridComponent != nullptr && spriteComponent != nullptr) {
			return Math::normalizePositionToGrid(position, spriteComponent->getGlobalBounds(), gridComponent->getTileSize());
		}
	}
	return position;
}
