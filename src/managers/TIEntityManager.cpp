#include "managers/TimeManager.h"
#include "managers/LogManager.h" 
#include "managers/TIEntityManager.h"
#include "managers/WindowManager.h"

#include "templates/MakeUnique.h"

using namespace TIE;

TIEntityManager::TIEntityManager() : clock(TimeManager::Instance()->addClock()) {
	sceneGraphRoot = make_unique<TIEntity>();
}


TIEntityManager::~TIEntityManager() {
	
}


SceneNode& TIEntityManager::getSceneGraphRoot() {
	return *this->sceneGraphRoot;
}


SceneNode& TIEntityManager::attachToSceneGraphRoot(std::unique_ptr<SceneNode> node) {
	SceneNode& reference = *node;
	sceneGraphRoot->attachChild(std::move(node));
	return reference;
}


SceneText& TIEntityManager::addSceneText(std::unique_ptr<SceneText> st) {
	GlobalId id = st->getId();
	sceneTexts[id] = std::move(st);
	LogManager::Instance()->logInfo("Added SceneText '" + std::to_string(id) + "'.");
	return getSceneText(id);
}


SceneText& TIEntityManager::getSceneText(GlobalId id) {
	if (sceneTexts.find(id) != sceneTexts.end()) {
		return *sceneTexts[id];
	} else {
		//implement exception
		return *sceneTexts[id];
	}
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


void TIEntityManager::removeSceneText(GlobalId id) {
	auto text = sceneTexts.find(id);
	if (text != sceneTexts.end()) {
		sceneTexts.erase(text);
		LogManager::Instance()->logInfo("Deleted SceneText '" + std::to_string(id) + "'.");
	} else {
		LogManager::Instance()->logError("SceneText '" + std::to_string(id) + "' does not exist, doing nothing.");	
	}
}


const std::map<GlobalId, std::unique_ptr<SceneText> >& TIEntityManager::getAllSceneTexts() {
	return sceneTexts;
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
