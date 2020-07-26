#include "managers/SceneManager.h"

#include <functional>

#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/GraphicsComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/SelectableComponentSystem.h"
#include "managers/LogManager.h" 
#include "managers/TimeManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "objects/SceneLayer.h"
#include "objects/entities/DegreeGuide.h"
#include "objects/entities/MousePtrCoords.h"
#include "templates/MakeUnique.h"

using namespace TIE;

SceneManager::SceneManager() : clock(TimeManager::Instance()->addClock()) {}

bool SceneManager::initialize() {
	this->sceneGraphRoot = make_unique<SceneLayer>();
	this->sceneGraphRoot->setLayer(SceneLayer::Layer::ROOT);
	this->sceneGraphRoot->setViewId(ViewManager::Instance()->getEngineViewId());
	this->sceneGraphRoot->setName("SceneGraphRoot");

	this->clientLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(make_unique<SceneLayer>()));
	this->clientLayer->setLayer(SceneLayer::Layer::CLIENT);
	this->clientLayer->setViewId(ViewManager::Instance()->getClientViewId());
	this->clientLayer->setName("ClientLayer");

	this->engineLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(make_unique<SceneLayer>()));
	this->engineLayer->setLayer(SceneLayer::Layer::ENGINE);
	this->engineLayer->setViewId(ViewManager::Instance()->getEngineViewId());
	this->engineLayer->setName("EngineLayer");

	std::unique_ptr<DegreeGuide> degreeGuide = make_unique<DegreeGuide>();
	degreeGuide->initialize();
	this->engineLayer->attachChild(std::move(degreeGuide));

	std::unique_ptr<MousePtrCoords> mousePtrCoords = make_unique<MousePtrCoords>();
	mousePtrCoords->initialize();
	this->engineLayer->attachChild(std::move(mousePtrCoords));

	return true;
}


SceneLayer& SceneManager::getSceneGraphRoot() {
	return *this->sceneGraphRoot;
}


SceneLayer& SceneManager::getEngineLayer() {
	return *this->engineLayer;
}


SceneLayer& SceneManager::getClientLayer() {
	return *this->clientLayer;
}


/* //Investigate with collides component
TIEntity* SceneManager::findTIEntity(sf::Vector2f point) {
	return this->getClientLayer().findNode(point);	
}
*/


void SceneManager::updateGameState() {

	this->delta = this->clock.restart().asSeconds();

	this->removeTIEntities(this->sceneGraphRoot->getChildren());
	this->updateGameState(this->sceneGraphRoot->getChildren());

	float fps = 60 / delta;
	this->windowManager->showFPS(std::to_string(fps));
}


void SceneManager::removeTIEntities(std::vector<std::unique_ptr<TIEntity> >& entities) {
	entities.erase(std::remove_if(entities.begin(), entities.end(), std::mem_fn(&TIEntity::getRemove)), entities.end());
	for (auto& entity : entities) {
		this->removeTIEntities(entity->getChildren());
	}
}


void SceneManager::updateGameState(const std::vector<std::unique_ptr<TIEntity> >& entities) {
	for (auto& entity : entities) {
		this->movesComponentSystem.update(*entity, this->delta);
		this->collidesComponentSystem.update(*entity, this->delta);
		this->selectableComponentSystem.update(*entity, this->delta);
		this->eventsComponentSystem.update(*entity, this->delta);

		entity->update(this->delta);

		for (auto& child : entity->getChildren()) {
			this->updateGameState(entity->getChildren());
		}
	}
}


void SceneManager::render() {		

	window.clear();

	sf::RenderStates states;

	ViewManager::Instance()->setActiveView(this->clientLayer->getViewId());
	GraphicsComponentSystem::draw(*(this->clientLayer), this->window, states);

	ViewManager::Instance()->setActiveView(this->engineLayer->getViewId());
	GraphicsComponentSystem::draw(*(this->engineLayer), this->window, states);

	window.display();
}
