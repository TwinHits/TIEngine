#include "componentsystems/GridComponentSystem.h"

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "managers/LogManager.h"
#include "utilities/TIEMath.h"

using namespace TIE;

void GridComponentSystem::update(TIEntity&, const float) {

}


sf::Vector2f GridComponentSystem::normalizePositionToGrid(const sf::Vector2f& position, TIEntity& gridEntity) {
	GridComponent* gridComponent = gridEntity.getComponent<GridComponent>();
	SpriteComponent* spriteComponent = gridEntity.getComponent<SpriteComponent>();
	if (gridComponent != nullptr && spriteComponent != nullptr) {
		return Math::normalizePositionToGrid(position, spriteComponent->getGlobalBounds(), gridComponent->getTileSize());
	}
	return position;
}
