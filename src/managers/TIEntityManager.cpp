#include "managers/LogManager.h"
#include "managers/TIEntityManager.h"

using namespace TIE;

TIEntityManager::TIEntityManager() {

}


TIEntityManager::~TIEntityManager() {
	
}


const TIEntity& TIEntityManager::addTIEntity(std::unique_ptr<TIEntity> e) {
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


const SceneText& TIEntityManager::addSceneText(std::unique_ptr<SceneText> st) {
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
