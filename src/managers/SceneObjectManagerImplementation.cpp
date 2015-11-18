#include "SceneObjectManager.h"
#include "LogManager.h"

SceneObjectManager::SceneObjectManager() {}

SceneObjectManager::~SceneObjectManager() 
{
	for (auto so = sceneObjects.begin(); so != sceneObjects.end(); ++so)
	{
		rmSceneObject(so->second->getId());
	}
}

const SceneObject& SceneObjectManager::addSceneObject(SceneObject* so)
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
		return *sceneObjects[id];
	}
}

void SceneObjectManager::rmSceneObject(GlobalId id)
{
	if (sceneObjects.find(id) != sceneObjects.end())
	{
		delete sceneObjects[id];
		LogManager::Instance()->logInfo("Deleted SceneObject'" + std::to_string(id) + "'.");
	}	
	else
	{
		LogManager::Instance()->logError("SceneObject '" + std::to_string(id) + "' does not exist, doing nothing.");	
	}
}

const std::map<GlobalId, SceneObject*>& SceneObjectManager::getAllSceneObjects()
{
	return sceneObjects;
}

void SceneObjectManager::updateGameState()
{
	for (auto so = sceneObjects.begin(); so != sceneObjects.end(); ++so)
	{
			so->second->update();
	}
}
