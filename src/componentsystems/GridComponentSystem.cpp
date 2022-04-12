#include "componentsystems/GridComponentSystem.h"

#include <SFML/Graphics.hpp>

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/WorldManager.h"
#include "managers/LogManager.h"
#include "utils/TIEMath.h"

using namespace TIE;

void GridComponentSystem::update(const float) {

}


void GridComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

    GridComponent& gridComponent = entity.addComponent<GridComponent>();
    SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();
    Components components = { gridComponent, spriteComponent };
    this->components.push_back(components);

    float width = factory.floatValues.at(GridComponentSystem::WIDTH);
    float height = factory.floatValues.at(GridComponentSystem::HEIGHT);
    gridComponent.setGridSize(sf::Vector2i(width, height));

    sf::FloatRect textureSize = spriteComponent.getLocalBounds();
    gridComponent.setTileSize(sf::Vector2f(textureSize.width / width, textureSize.height / height));
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


std::string GridComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	return "";
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
