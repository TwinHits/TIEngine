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

void SceneObjectManager::addSceneObject(SceneObject* so)
{
	sceneObjects[so->getId()] = so;
	LogManager::Instance()->logInfo("Added SceneObject '" + std::to_string(so->getId()) + "'.");
}

const SceneObject& SceneObjectManager::getSceneObject(unsigned long id)
{
	return *sceneObjects[id];
}

void SceneObjectManager::rmSceneObject(unsigned long id)
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

const std::map<unsigned long, SceneObject*>& SceneObjectManager::getAllSceneObjects()
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
