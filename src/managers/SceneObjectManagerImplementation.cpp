#include "SceneObjectManager.h"
#include "LogManager.h"

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
		return *sceneObjects[id];
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
