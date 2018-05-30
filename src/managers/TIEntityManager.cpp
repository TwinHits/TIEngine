#include "managers/LogManager.h"
#include "managers/TIEntityManager.h"

using namespace TIE;

TIEntityManager::TIEntityManager() {

}


TIEntityManager::~TIEntityManager() {
	
}


TIEntity& TIEntityManager::addTIEntity(std::unique_ptr<TIEntity> e) {
	GlobalId id = e->getId();
	sceneObjects[id] = std::move(e);
	LogManager::Instance()->logInfo("Added TIEntity '" + std::to_string(id) + "'.");
	return getTIEntity(id);
}


TIEntity& TIEntityManager::getTIEntity(GlobalId id) {
	if (sceneObjects.find(id) != sceneObjects.end()) {
		return *sceneObjects[id];
	} else {
		//implement exception
		return *sceneObjects[id];
	}
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


void TIEntityManager::removeTIEntity(GlobalId id) {
	auto object = sceneObjects.find(id);
	if (object != sceneObjects.end()) {
		sceneObjects.erase(object);
		LogManager::Instance()->logInfo("Deleted TIEntity '" + std::to_string(id) + "'.");
	} else {
		LogManager::Instance()->logError("TIEntity '" + std::to_string(id) + "' does not exist, doing nothing.");	
	}
}


const std::map<GlobalId, std::unique_ptr<TIEntity> >& TIEntityManager::getAllTIEntitys() {
	return sceneObjects;
}


void TIEntityManager::updateGameState() {
	for (auto& e: sceneObjects) {
			e.second->update();
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
	//Gets all the tientities and checks their texture rectangles for collisions
	//if they are drawn
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
	return;	
}
