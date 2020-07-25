#include "managers/GridManager.h"

#include "objects/components/GridComponent.h"
#include "managers/LogManager.h"
#include "objects/entities/TIEntity.h"

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


