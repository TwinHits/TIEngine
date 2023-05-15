#include "managers/WorldManager.h"

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/tientities/engine/GridGuide.h"
#include "objects/factories/SceneLayerFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "templates/MakeUnique.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

void WorldManager::initialize() {
	this->worldLayer = &SceneLayerFactory()
		.setParent(SceneManager::Instance()->getClientLayer())
		.setViewId(ViewManager::Instance()->getClientViewId())
		.setName("WorldLayer")
	.build();
}


bool WorldManager::isGridConfigured() {
	return this->gridComponent != nullptr;
}


TIEntity* WorldManager::getLevelEntity() {
	return this->levelEntity;
}


void WorldManager::setLevelEntity(TIEntityFactory& factory) {
	factory.setParent(this->worldLayer);
	this->levelEntity = &factory.build();
	this->gridComponent = this->levelEntity->getComponent<GridComponent>();
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
			ComponentSystems::setDrawn(*(this->gridGuide), visibility);
		}
	} else {
		LogManager::Instance()->warn("No grid is currently configured.");
	}
}

TIEntity& WorldManager::registerTIEntity(TIEntity& tientity) {
    this->tientities[tientity.getId()] = &tientity;
    return tientity;
}


TIEntity* WorldManager::getTIEntityById(GlobalId id) {
	return this->tientities.count(id) ? this->tientities.at(id) : nullptr;
}


TIEntityFactory& WorldManager::saveTIEntityFactory(const std::string& name, TIEntityFactory& factory) {
	this->tiEntityFactories.insert({ name, make_unique<TIEntityFactory>(factory) });
	return *this->tiEntityFactories.at(name);
}


TIEntityFactory* WorldManager::getTIEntityFactory(const std::string& name) {
	if (this->tiEntityFactories.count(name)) {
		return this->tiEntityFactories.at(name).get();
	} else {
		return nullptr;
	}
}


FiniteStateMachineFactory& WorldManager::saveFiniteStateMachineFactory(GlobalId id, FiniteStateMachineFactory& factory) {
	this->finiteStateMachineFactories.insert({ id, make_unique<FiniteStateMachineFactory>(factory) });
	return *this->finiteStateMachineFactories.at(id);
}


FiniteStateMachineFactory* WorldManager::getFiniteStateMachineFactory(GlobalId id) {
	if (this->finiteStateMachineFactories.count(id)) {
		return this->finiteStateMachineFactories.at(id).get();
	} else {
		return nullptr;
	}
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
