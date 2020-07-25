#include "componentsystems/GridComponentSystem.h"

#include "objects/entities/TIEntity.h"
#include "managers/LogManager.h"

using namespace TIE;

void GridComponentSystem::update(TIEntity&, const float) {

}


sf::Vector2f GridComponentSystem::normalizePositionToGrid(GridComponent* gridComponent, const sf::Vector2f& position) {
	if (gridComponent != nullptr) {
		const sf::Vector2i& gridSize = gridComponent->getGridSize();
		const sf::Vector2f& tileSize = gridComponent->getTileSize();

		sf::Vector2f normalizedPosition;
		normalizedPosition.x = (int)(position.x / tileSize.x) * tileSize.x;
		normalizedPosition.y = (int)(position.y / tileSize.y) * tileSize.y;
		return normalizedPosition;
	}
	return position;
}
