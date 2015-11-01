#include "SceneObjectManager.h"
#include "HashManager.h"
#include "LogManager.h"

SceneObjectManager::SceneObjectManager() {}
SceneObjectManager::~SceneObjectManager() {}

const SceneObject& SceneObjectManager::addSceneObject()
{
	unsigned long id = HashManager::Instance()->getNewHash();
	if (sceneObjects.find(id) == sceneObjects.end())
	{		
		sceneObjects[id] = new SceneObject(id);
		LogManager::Instance()->logInfo("Added SceneObject '" + std::to_string(id) + "'.");
		return *sceneObjects[id];
	}
	else
	{
		LogManager::Instance()->logWarn("Hash collison! SceneObject '" + std::to_string(id) + "' already exists. Recursively rehashing.");
		return addSceneObject();
	}
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
