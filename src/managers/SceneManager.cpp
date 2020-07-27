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

	this->updateTIEntities(this->sceneGraphRoot->getChildren());
	ViewManager::Instance()->updateCamera(this->delta);

	std::string fps = this->calculateRollingAverageFPS(this->delta);
	this->windowManager->showFPS(fps);
}


void SceneManager::removeTIEntities(std::vector<std::unique_ptr<TIEntity> >& entities) {
	entities.erase(std::remove_if(entities.begin(), entities.end(), std::mem_fn(&TIEntity::getRemove)), entities.end());
}


void SceneManager::updateTIEntities(const std::vector<std::unique_ptr<TIEntity> >& entities) {
	for (auto& entity : entities) {

		if (entity->getComponent<SpriteComponent>() != nullptr) {
			this->movesComponentSystem.update(*entity, this->delta);
			this->collidesComponentSystem.update(*entity, this->delta);
		}

		if (EventsManager::Instance()->isEvents()) {
			this->selectableComponentSystem.update(*entity, this->delta);
			this->eventsComponentSystem.update(*entity, this->delta);
		}

		entity->update(this->delta);

		for (auto& child : entity->getChildren()) {
			this->removeTIEntities(child->getChildren());
			this->updateTIEntities(child->getChildren());
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


std::string SceneManager::calculateRollingAverageFPS(const float delta) {
	static int index=0;
	static int sum=0;
	static int ticks[100] = { 0 };

	int tick = 60 / delta;

	sum -= ticks[index];
	sum += tick;
	ticks[index] = tick;
	if (++index == 100) {
		index = 0;
	}

	return std::to_string(sum / 100);

}
