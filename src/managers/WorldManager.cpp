#include "managers/WorldManager.h"

#include "componentsystems/ShapeComponentSystem.h"
#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/entities/GridGuide.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "templates/MakeUnique.h"
#include "utils/Graphics.h"

using namespace TIE;

bool WorldManager::initialize() {
	return true;
}


bool WorldManager::isGridConfigured() {
	return this->gridComponent != nullptr;
}


TIEntity* WorldManager::getLevelEntity() {
	return this->levelEntity;
}


void WorldManager::setLevelEntity(TIEntity& tientity) {
	this->levelEntity = &tientity;
	this->gridComponent = tientity.getComponent<GridComponent>();
	SpriteComponent* spriteComponent = this->levelEntity->getComponent<SpriteComponent>();
	this->recalculateScrollBounds(*spriteComponent);
}


GridComponent* WorldManager::getGridComponent() {
	return this->gridComponent;
}


void WorldManager::showGridGuide(bool visibility) {
	if (this->isGridConfigured()) {
		if (this->gridGuide == nullptr) {
			this->recalculateGrideGuide(this->gridComponent);
		}

		if (this->gridGuide != nullptr) {
			Graphics::setDrawn(*(this->gridGuide), visibility);
		}
	} else {
		LogManager::Instance()->warn("No grid is currently configured.");
	}
}


TIEntityFactory& WorldManager::registerTIEntity(const std::string& tientityName) {
	this->tientityDefinitions.insert({ tientityName, TIEntityFactory() });
	return this->tientityDefinitions.at(tientityName);
}


void WorldManager::spawnTIEntity(const std::string& tientityName) {
	if (this->tientityDefinitions.count(tientityName)) {
		this->spawnedTIEntityDefinitions.push_back(tientityName);
	} else {
		LogManager::Instance()->warn("Entity " + tientityName + " does not exist.");
	}
}


void WorldManager::attachNewTIEntities() {
	for (auto& definition : this->spawnedTIEntityDefinitions) {
		tientityDefinitions.at(definition).build();
	}
	this->spawnedTIEntityDefinitions.clear();
}


void WorldManager::recalculateGrideGuide(GridComponent* gridComponent) {
	if (this->gridGuide != nullptr) {
		this->gridGuide->setRemove(true);
	}

	if (this->isGridConfigured()) {
		this->gridGuide = &dynamic_cast<GridGuide&>(SceneManager::Instance()->getClientLayer().attachChild(make_unique<GridGuide>()));
		SpriteComponent* spriteComponent = this->levelEntity->getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			this->gridGuide->initialize(spriteComponent->getGlobalBounds(), this->gridComponent->getGridSize(), this->gridComponent->getTileSize());
			this->recalculateScrollBounds(*spriteComponent);
		}
	} else {
		LogManager::Instance()->warn("No grid is currently configured.");
	}
}


void WorldManager::recalculateScrollBounds(const SpriteComponent& spriteComponent) {
	ViewManager::Instance()->setScrollBounds(spriteComponent.getGlobalBounds());
}
