#include "managers/SceneManager.h"

#include <functional>

#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/GraphicsComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
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

	this->delta += this->clock.restart().asSeconds();
	TIEntity& sceneGraph = this->getSceneGraphRoot();

	while (this->delta > this->TimePerFrame) {

		this->removeTIEntities(sceneGraphRoot->getChildren());
		this->executeComponentSystems(sceneGraphRoot->getChildren());

		float fps = 60 / delta;
		WindowManager::Instance()->showFPS(std::to_string(fps));
		this->delta = 0;
	}
}


void SceneManager::removeTIEntities(std::vector<std::unique_ptr<TIEntity> >& entities) {
	auto removesBegin = std::remove_if(entities.begin(), entities.end(), std::mem_fn(&TIEntity::getRemove));
	entities.erase(removesBegin, entities.end());
	for (auto& entity : entities) {
		this->removeTIEntities(entity->getChildren());
	}
}

void SceneManager::executeComponentSystems(const std::vector<std::unique_ptr<TIEntity> >& entities) {
	for (auto& entity : entities) {
		MovesComponentSystem().execute(*entity, this->delta);
		CollidesComponentSystem().execute(*entity, this->delta);
		entity->update(this->delta);

		for (auto& child : entity->getChildren()) {
			this->executeComponentSystems(entity->getChildren());
		}
	}
}


void SceneManager::render() {		

	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	sf::RenderStates states;
	SceneLayer& clientLayer = this->getClientLayer();
	SceneLayer& engineLayer = this->getEngineLayer();

	window.clear();

	ViewManager::Instance()->setActiveView(clientLayer.getViewId());
	GraphicsComponentSystem::draw(clientLayer, window, states);

	ViewManager::Instance()->setActiveView(engineLayer.getViewId());
	GraphicsComponentSystem::draw(engineLayer, window, states);

	window.display();
}
