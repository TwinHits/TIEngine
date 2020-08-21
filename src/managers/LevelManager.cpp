#include "managers/LevelManager.h"

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

bool LevelManager::initialize() {
	return true;
}


bool LevelManager::isGridConfigured() {
	return this->gridComponent != nullptr;
}


TIEntity* LevelManager::getLevelEntity() {
	return this->levelEntity;
}


void LevelManager::setLevelEntity(TIEntity& tientity) {
	this->levelEntity = &tientity;
	this->gridComponent = tientity.getComponent<GridComponent>();
	SpriteComponent* spriteComponent = this->levelEntity->getComponent<SpriteComponent>();
	this->recalculateScrollBounds(*spriteComponent);
}


GridComponent* LevelManager::getGridComponent() {
	return this->gridComponent;
}


void LevelManager::showGridGuide(bool visibility) {
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


void LevelManager::recalculateGrideGuide(GridComponent* gridComponent) {
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


void LevelManager::recalculateScrollBounds(const SpriteComponent& spriteComponent) {
	ViewManager::Instance()->setScrollBounds(spriteComponent.getGlobalBounds());
}
