#include "managers/SceneObjectManager.h"
#include "managers/LogManager.h"

using namespace TIE;

SceneObjectManager::SceneObjectManager() {}

SceneObjectManager::~SceneObjectManager() {}

const SceneObject& SceneObjectManager::addSceneObject(std::shared_ptr<SceneObject> so)
{
	sceneObjects[so->getId()] = so;
	LogManager::Instance()->logInfo("Added SceneObject '" + std::to_string(so->getId()) + "'.");
	return getSceneObject(so->getId());
}

const SceneObject& SceneObjectManager::getSceneObject(GlobalId id)
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

const SceneText& SceneObjectManager::addSceneText(std::shared_ptr<SceneText> st)
{
	sceneTexts[st->getId()] = st;
	LogManager::Instance()->logInfo("Added SceneText '" + std::to_string(st->getId()) + "'.");
	return getSceneText(st->getId());
}

const SceneText& SceneObjectManager::getSceneText(GlobalId id)
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

void SceneObjectManager::rmSceneObject(GlobalId id)
{
	auto object = sceneObjects.find(id);
	if (object != sceneObjects.end())
	{
		sceneObjects.erase(object);
		LogManager::Instance()->logInfo("Deleted SceneObject'" + std::to_string(id) + "'.");
	}	
	else
	{
		LogManager::Instance()->logError("SceneObject '" + std::to_string(id) + "' does not exist, doing nothing.");	
	}
}

const std::map<GlobalId, std::shared_ptr<SceneObject> >& SceneObjectManager::getAllSceneObjects()
{
	return sceneObjects;
}

void SceneObjectManager::updateGameState()
{
	for (auto& so: sceneObjects)
	{
			so.second->update();
	}
}

void SceneObjectManager::rmSceneText(GlobalId id)
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

const std::map<GlobalId, std::shared_ptr<SceneText> >& SceneObjectManager::getAllSceneTexts()
{
	return sceneTexts;
}
