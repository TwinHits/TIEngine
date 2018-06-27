#include "managers/TimeManager.h"
#include "managers/LogManager.h" 
#include "managers/TIEntityManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"

#include "objects/SceneLayer.h"

#include "templates/MakeUnique.h"

using namespace TIE;

TIEntityManager::TIEntityManager() : clock(TimeManager::Instance()->addClock()) {
	GlobalId engineViewId = ViewManager::Instance()->addView();
	GlobalId clientViewId = ViewManager::Instance()->addView();

	this->sceneGraphRoot = make_unique<SceneLayer>();
	this->sceneGraphRoot->setLayer(SceneLayer::Layer::ROOT);
	this->sceneGraphRoot->setName("ROOT");
	this->sceneGraphRoot->setPosition(0,0);
	this->sceneGraphRoot->setViewId(engineViewId);

	std::unique_ptr<SceneLayer> clientLayerPtr = make_unique<SceneLayer>();
	clientLayerPtr->setLayer(SceneLayer::Layer::CLIENT);
	clientLayerPtr->setName("client layer");
	clientLayerPtr->setViewId(clientViewId);
	this->clientLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(std::move(clientLayerPtr)));

	std::unique_ptr<SceneLayer> engineLayerPtr = make_unique<SceneLayer>();
	engineLayerPtr->setLayer(SceneLayer::Layer::ENGINE);
	engineLayerPtr->setName("engine layer");
	engineLayerPtr->setViewId(engineViewId);
	this->engineLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(std::move(engineLayerPtr)));
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


void TIEntityManager::updateGameState() {
	this->delta += this->clock.restart().asSeconds();

	while (this->delta > this->TimePerFrame) {

		sceneGraphRoot->update(delta);

		float fps = 60 / delta;
		WindowManager::Instance()->showFPS(std::to_string(fps));
		this->delta = 0;
	}
}


std::vector<GlobalId> TIEntityManager::getCollidingTIEntities(DetectionStrategy strategy, TIEntity& entity) {
	std::vector<GlobalId> ids;

	if (!entity.getCollidable()) {
		return ids;
	}

	if (strategy == DetectionStrategy::SIMPLE) {
		simple(ids, entity);
	}

	return ids;
}


void TIEntityManager::simple(std::vector<GlobalId>& ids, TIEntity& entity) {
	//Requires a significant refactoring to go before this can be reimplemented.
	/**
	const std::map<GlobalId, std::unique_ptr<TIEntity> >&  entities = this->getAllTIEntitys();
	sf::FloatRect hitbox = entity.getSprite().getGlobalBounds();
	for (auto& e : entities) {
		if (e.second->getCollidable() && entity.getId() != e.second->getId()) {
			sf::FloatRect rect = e.second->getSprite().getGlobalBounds();
			if (hitbox.intersects(rect)) {
				ids.push_back(e.second->getId());	
			}
		}
	}
	**/
	return;	
}
