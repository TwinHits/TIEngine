#include "managers/GridManager.h"

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/entities/GridGuide.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

bool GridManager::initialize() {
	return true;
}


bool GridManager::isGridConfigured() {
	return this->gridEntity != nullptr;
}


TIEntity* GridManager::getGridEntity() {
	return this->gridEntity;
}


void GridManager::setGridEntity(TIEntity& tientity) {
	this->gridComponent = tientity.getComponent<GridComponent>();
	if (this->gridComponent != nullptr) {
		this->gridEntity = &tientity;
	} else {
		this->gridEntity = nullptr;
		this->gridComponent = nullptr;
		LogManager::Instance()->error("This entity does not have a grid component: " + tientity.getName() + ".");
	}
}


GridComponent* GridManager::getGridComponent() {
	return this->gridComponent;
}


void GridManager::showGridGuide(bool visibility) {
	if (this->gridGuide == nullptr) {
		this->recalculateGrideGuide(this->gridComponent);
	}

	if (this->gridGuide != nullptr) {
		GraphicsComponentSystem::setDrawn(*(this->gridGuide), visibility);
	} 
}


void GridManager::recalculateGrideGuide(GridComponent* gridComponent) {
	if (this->gridGuide != nullptr) {
		this->gridGuide->setRemove(true);
	}

	if (this->isGridConfigured()) {
		this->gridGuide = &dynamic_cast<GridGuide&>(SceneManager::Instance()->getClientLayer().attachChild(make_unique<GridGuide>()));
		SpriteComponent* spriteComponent = this->gridEntity->getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			this->gridGuide->initialize(spriteComponent->getPosition(), this->gridComponent->getGridSize(), this->gridComponent->getTileSize());
		}
	} else {
		LogManager::Instance()->warn("No grid is currently configured.");
	}
}

