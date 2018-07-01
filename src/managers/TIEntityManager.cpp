#include "managers/TimeManager.h"
#include "managers/LogManager.h" 
#include "managers/TIEntityManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"

#include "objects/SceneLayer.h"
#include "objects/drawables/MousePtrCoords.h"

#include "templates/MakeUnique.h"

using namespace TIE;

TIEntityManager::TIEntityManager() : clock(TimeManager::Instance()->addClock()) {
	GlobalId engineViewId = ViewManager::Instance()->addView();
	GlobalId clientViewId = ViewManager::Instance()->addView();

	this->sceneGraphRoot = make_unique<SceneLayer>();
	this->sceneGraphRoot->setLayer(SceneLayer::Layer::ROOT);
	this->sceneGraphRoot->setType("ROOT");
	this->sceneGraphRoot->setPosition(0,0);
	this->sceneGraphRoot->setViewId(engineViewId);

	std::unique_ptr<SceneLayer> clientLayerPtr = make_unique<SceneLayer>();
	clientLayerPtr->setLayer(SceneLayer::Layer::CLIENT);
	clientLayerPtr->setType("Client Layer");
	clientLayerPtr->setViewId(clientViewId);
	this->clientLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(std::move(clientLayerPtr)));

	std::unique_ptr<SceneLayer> engineLayerPtr = make_unique<SceneLayer>();
	engineLayerPtr->setLayer(SceneLayer::Layer::ENGINE);
	engineLayerPtr->setType("Engine Layer");
	engineLayerPtr->setViewId(engineViewId);
	this->engineLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(std::move(engineLayerPtr)));

	std::unique_ptr<MousePtrCoords> mousePtrCoords = make_unique<MousePtrCoords>();
	this->engineLayer->attachChild(std::move(mousePtrCoords));
}


TIEntityManager::~TIEntityManager() {
	
}


SceneLayer& TIEntityManager::getSceneGraphRoot() {
	return *this->sceneGraphRoot;
}


SceneLayer& TIEntityManager::getEngineLayer() {
	return *this->engineLayer;
}


SceneLayer& TIEntityManager::getClientLayer() {
	return *this->clientLayer;
}


void TIEntityManager::checkForCollisions() {
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


void TIEntityManager::updateGameState() {

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


void TIEntityManager::removeNodes() {
	this->sceneGraphRoot->removeNodes();
}
