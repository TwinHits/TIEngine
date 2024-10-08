#include "componentsystems/GridComponentSystem.h"

#include <SFML/Graphics.hpp>
 
#include "componentsystems/SpriteComponentSystem.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "utils/TIEMath.h"

using namespace TIE;

GridComponentSystem::GridComponentSystem() {
	this->setName(GridComponentSystem::GRID);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(GridComponentSystem::WIDTH, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(GridComponentSystem::HEIGHT, this);
}


void GridComponentSystem::update(const float) {}


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
	const ScriptTableReader& reader = factory.getReader().getReader(GridComponentSystem::GRID);

    const float& width = *reader.get<float>(GridComponentSystem::WIDTH);
    const float& height = *reader.get<float>(GridComponentSystem::HEIGHT);
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


sol::object GridComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
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
