#include "managers/TIEntityManager.h"
#include "managers/LogManager.h"

using namespace TIE;

TIEntityManager::TIEntityManager() {}

TIEntityManager::~TIEntityManager() {}

const TIEntity& TIEntityManager::addTIEntity(std::shared_ptr<TIEntity> so)
{
	sceneObjects[so->getId()] = so;
	LogManager::Instance()->logInfo("Added TIEntity '" + std::to_string(so->getId()) + "'.");
	return getTIEntity(so->getId());
}

const TIEntity& TIEntityManager::getTIEntity(GlobalId id)
{
	if (sceneObjects.find(id) != sceneObjects.end())
	{
		return *sceneObjects[id];
	}
	else 
	{
		//implement exception
		return *sceneObjects[id];
	}
}

const SceneText& TIEntityManager::addSceneText(std::shared_ptr<SceneText> st)
{
	sceneTexts[st->getId()] = st;
	LogManager::Instance()->logInfo("Added SceneText '" + std::to_string(st->getId()) + "'.");
	return getSceneText(st->getId());
}

const SceneText& TIEntityManager::getSceneText(GlobalId id)
{
	if (sceneTexts.find(id) != sceneTexts.end())
	{
		return *sceneTexts[id];
	}
	else 
	{
		//implement exception
		return *sceneTexts[id];
	}
}

void TIEntityManager::rmTIEntity(GlobalId id)
{
	auto object = sceneObjects.find(id);
	if (object != sceneObjects.end())
	{
		sceneObjects.erase(object);
		LogManager::Instance()->logInfo("Deleted TIEntity'" + std::to_string(id) + "'.");
	}	
	else
	{
		LogManager::Instance()->logError("TIEntity '" + std::to_string(id) + "' does not exist, doing nothing.");	
	}
}

const std::map<GlobalId, std::shared_ptr<TIEntity> >& TIEntityManager::getAllTIEntitys()
{
	return sceneObjects;
}

void TIEntityManager::updateGameState()
{
	for (auto& so: sceneObjects)
	{
			so.second->update();
	}
}

void TIEntityManager::rmSceneText(GlobalId id)
{
	auto text = sceneTexts.find(id);
	if (text != sceneTexts.end())
	{
		sceneTexts.erase(text);
		LogManager::Instance()->logInfo("Deleted SceneText " + std::to_string(id) + "'.");
	}	
	else
	{
		LogManager::Instance()->logError("SceneText '" + std::to_string(id) + "' does not exist, doing nothing.");	
	}
}

const std::map<GlobalId, std::shared_ptr<SceneText> >& TIEntityManager::getAllSceneTexts()
{
	return sceneTexts;
}
