#include "managers/GridManager.h"

#include "componentsystems/ShapeComponentSystem.h"
#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/entities/GridGuide.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "templates/MakeUnique.h"
#include "utilities/Graphics.h"

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
		SpriteComponent* spriteComponent = this->gridEntity->getComponent<SpriteComponent>();
		this->recalculateScrollBounds(*spriteComponent);
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
		Graphics::setDrawn(*(this->gridGuide), visibility);
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
			this->gridGuide->initialize(spriteComponent->getGlobalBounds(), this->gridComponent->getGridSize(), this->gridComponent->getTileSize());
			this->recalculateScrollBounds(*spriteComponent);
		}
	} else {
		LogManager::Instance()->warn("No grid is currently configured.");
	}
}


void GridManager::recalculateScrollBounds(const SpriteComponent& spriteComponent) {
	ViewManager::Instance()->setScrollBounds(spriteComponent.getGlobalBounds());
}
