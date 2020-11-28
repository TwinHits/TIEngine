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

	if (factory.floatValues.count(GridComponentSystem::WIDTH) && factory.floatValues.count(GridComponentSystem::HEIGHT)) {
		GridComponent& gridComponent = entity.addComponent<GridComponent>();
		SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();
		Components components = { gridComponent, spriteComponent };

		float width = factory.floatValues.at(GridComponentSystem::WIDTH);
		float height = factory.floatValues.at(GridComponentSystem::HEIGHT);
		gridComponent.setGridSize(sf::Vector2i(width, height));

		sf::FloatRect textureSize = spriteComponent.getLocalBounds();
		gridComponent.setTileSize(sf::Vector2f(textureSize.width / width, textureSize.height / height));

		WorldManager::Instance()->setLevelEntity(entity);
		this->components.push_back(components);
	}
}


const std::string& GridComponentSystem::getName() {
	return GridComponentSystem::GRID;
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
