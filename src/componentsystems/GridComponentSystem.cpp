#include "componentsystems/GridComponentSystem.h"

#include <SFML/Graphics.hpp>

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/GridManager.h"
#include "managers/LogManager.h"
#include "utilities/TIEMath.h"

using namespace TIE;

const std::string GridComponentSystem::GRID = "grid";
const std::string GridComponentSystem::WIDTH = "width";
const std::string GridComponentSystem::HEIGHT = "height";
const std::string GridComponentSystem::WIDTH_KEY = GridComponentSystem::GRID + '.' + GridComponentSystem::WIDTH;
const std::string GridComponentSystem::HEIGHT_KEY = GridComponentSystem::GRID + '.' + GridComponentSystem::HEIGHT;

void GridComponentSystem::update(TIEntity&, const float) {

}


GridComponent* TIE::GridComponentSystem::addGridComponent(const TIEntityFactory& factory, TIEntity& entity) {

	GridComponent* gridComponent = nullptr;
	if (factory.floatValues.count(GridComponentSystem::WIDTH_KEY) && factory.floatValues.count(GridComponentSystem::HEIGHT_KEY)) {
		float width = factory.floatValues.at(GridComponentSystem::WIDTH_KEY);
		float height = factory.floatValues.at(GridComponentSystem::HEIGHT_KEY);
		gridComponent = entity.addComponent<GridComponent>();
		gridComponent->setGridSize(sf::Vector2i(width, height));

		SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			sf::FloatRect textureSize = spriteComponent->getLocalBounds();
			gridComponent->setTileSize(sf::Vector2f(textureSize.width / width, textureSize.height / height));
		}

		GridManager::Instance()->setGridEntity(entity);
	}

	return gridComponent;
}


sf::Vector2f GridComponentSystem::normalizePositionToGrid(const sf::Vector2f& position) {
	if (GridManager::Instance()->isGridConfigured()) {
		TIEntity* gridEntity = GridManager::Instance()->getGridEntity();
		GridComponent* gridComponent = gridEntity->getComponent<GridComponent>();
		SpriteComponent* spriteComponent = gridEntity->getComponent<SpriteComponent>();
		if (gridComponent != nullptr && spriteComponent != nullptr) {
			return Math::normalizePositionToGrid(position, spriteComponent->getGlobalBounds(), gridComponent->getTileSize());
		}
	}
	return position;
}
