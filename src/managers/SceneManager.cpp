#include "managers/TimeManager.h"
#include "managers/LogManager.h" 
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"

#include "managers/componentsystems/CollidesComponentSystem.h"
#include "managers/componentsystems/GraphicsComponentSystem.h"
#include "managers/componentsystems/MovesComponentSystem.h"

#include "objects/SceneLayer.h"
#include "objects/entities/DegreeGuide.h"
#include "objects/entities/MousePtrCoords.h"

#include "templates/MakeUnique.h"

using namespace TIE;

SceneManager::SceneManager() : clock(TimeManager::Instance()->addClock()) {
	this->sceneGraphRoot = make_unique<SceneLayer>();
	this->sceneGraphRoot->setLayer(SceneLayer::Layer::ROOT);
	this->sceneGraphRoot->setViewId(ViewManager::Instance()->getEngineViewId());
	this->sceneGraphRoot->setName("SceneGraphRoot");

	std::unique_ptr<SceneLayer> clientLayerPtr = make_unique<SceneLayer>();
	clientLayerPtr->setLayer(SceneLayer::Layer::CLIENT);
	clientLayerPtr->setViewId(ViewManager::Instance()->getClientViewId());
	this->clientLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(std::move(clientLayerPtr)));
	this->clientLayer->setName("ClientLayer");

	std::unique_ptr<SceneLayer> engineLayerPtr = make_unique<SceneLayer>();
	engineLayerPtr->setLayer(SceneLayer::Layer::ENGINE);
	engineLayerPtr->setViewId(ViewManager::Instance()->getEngineViewId());
	this->engineLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(std::move(engineLayerPtr)));
	this->clientLayer->setName("EngineLayer");

	std::unique_ptr<DegreeGuide> degreeGuide = make_unique<DegreeGuide>();
	degreeGuide->initialize();
	this->engineLayer->attachChild(std::move(degreeGuide));

	std::unique_ptr<MousePtrCoords> mousePtrCoords = make_unique<MousePtrCoords>();
	mousePtrCoords->initialize();
	this->engineLayer->attachChild(std::move(mousePtrCoords));

}


SceneManager::~SceneManager() {
	
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

		this->removeNodes();
		this->executeComponentSystems(sceneGraphRoot->getChildren());

		float fps = 60 / delta;
		WindowManager::Instance()->showFPS(std::to_string(fps));
		this->delta = 0;
	}
}


void SceneManager::removeNodes() {
	this->sceneGraphRoot->removeNodes();
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
	GraphicsComponentSystem::draw(clientLayer.getChildren(), window, states);

	ViewManager::Instance()->setActiveView(engineLayer.getViewId());
	GraphicsComponentSystem::draw(engineLayer.getChildren(), window, states);

	window.display();
}
