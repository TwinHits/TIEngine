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

void GridComponentSystem::update(TIEntity&, const float) {

}


GridComponent* TIE::GridComponentSystem::addGridComponent(const TIEntityFactory& factory, TIEntity& entity) {
	GridComponent* gridComponent = nullptr;
	auto width = factory.floatValues.find("grid.width");
	auto height = factory.floatValues.find("grid.height");

	auto end = factory.floatValues.end();
	if (width != end && height != end) {
		gridComponent = entity.addComponent<GridComponent>();
		gridComponent->setGridSize(sf::Vector2i(width->second, height->second));

		SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			sf::FloatRect textureSize = spriteComponent->getLocalBounds();
			gridComponent->setTileSize(sf::Vector2f(textureSize.width / width->second, textureSize.height / height->second));
		}

		GridManager::Instance()->setGridEntity(entity);
	}

	return gridComponent;
}


sf::Vector2f GridComponentSystem::normalizePositionToGrid(const sf::Vector2f& position, TIEntity& gridEntity) {
	GridComponent* gridComponent = gridEntity.getComponent<GridComponent>();
	SpriteComponent* spriteComponent = gridEntity.getComponent<SpriteComponent>();
	if (gridComponent != nullptr && spriteComponent != nullptr) {
		return Math::normalizePositionToGrid(position, spriteComponent->getGlobalBounds(), gridComponent->getTileSize());
	}
	return position;
}
