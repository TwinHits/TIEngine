#include "managers/TimeManager.h"
#include "managers/LogManager.h" 
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"

#include "objects/SceneLayer.h"
#include "objects/drawables/MousePtrCoords.h"

#include "templates/MakeUnique.h"

using namespace TIE;

SceneManager::SceneManager() : clock(TimeManager::Instance()->addClock()) {
	this->sceneGraphRoot = make_unique<SceneLayer>();
	this->sceneGraphRoot->setLayer(SceneLayer::Layer::ROOT);
	this->sceneGraphRoot->setType("ROOT");
	this->sceneGraphRoot->setPosition(0, 0);
	this->sceneGraphRoot->setViewId(ViewManager::Instance()->getEngineViewId());

	std::unique_ptr<SceneLayer> clientLayerPtr = make_unique<SceneLayer>();
	clientLayerPtr->setLayer(SceneLayer::Layer::CLIENT);
	clientLayerPtr->setType("Client Layer");
	clientLayerPtr->setViewId(ViewManager::Instance()->getClientViewId());
	this->clientLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(std::move(clientLayerPtr)));

	std::unique_ptr<SceneLayer> engineLayerPtr = make_unique<SceneLayer>();
	engineLayerPtr->setLayer(SceneLayer::Layer::ENGINE);
	engineLayerPtr->setType("Engine Layer");
	engineLayerPtr->setViewId(ViewManager::Instance()->getEngineViewId());
	this->engineLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(std::move(engineLayerPtr)));

	std::unique_ptr<MousePtrCoords> mousePtrCoords = make_unique<MousePtrCoords>();
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


SceneNode* SceneManager::findSceneNode(sf::Vector2f point) {
	return this->getClientLayer().findNode(point);	
}


void SceneManager::removeNodes() {
	this->sceneGraphRoot->removeNodes();
}


void SceneManager::checkForCollisions() {
	this->collisions.clear();
	
	SceneLayer& sceneGraphRoot = this->getSceneGraphRoot();
	sceneGraphRoot.checkSceneCollisions(sceneGraphRoot, this->collisions);

	if (!collisions.empty()) {
		for (auto& pair : collisions) {
			pair.first->collide(pair.second);
			pair.second->collide(pair.first);
		}
	}
}


void SceneManager::updateGameState() {

	this->delta += this->clock.restart().asSeconds();
	while (this->delta > this->TimePerFrame) {

		this->removeNodes();
		this->checkForCollisions();
		sceneGraphRoot->update(delta);

		float fps = 60 / delta;
		WindowManager::Instance()->showFPS(std::to_string(fps));
		this->delta = 0;
	}
}


void SceneManager::render() {		
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();

	SceneNode& sceneGraph = SceneManager::Instance()->getSceneGraphRoot();
	sf::RenderStates states;

	window.clear();
	sceneGraph.draw(window, states);
	window.display();
}
